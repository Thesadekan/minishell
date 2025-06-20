/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:02:58 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/20 09:30:21 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig g_sig;

void handle_redirection(t_mini *mini, t_redirections *redir)
{
    int fd;
    if (redir->type == TRUNC)
        fd = open(redir->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (redir->type == APPEND)
        fd = open(redir->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else
        return;

    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(redir->value, STDERR_FILENO);
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);
        mini->ret = 1;
        mini->no_exec = 1;
        return;
    }

    if (dup2(fd, STDOUT_FILENO) == -1)
        perror("dup2");

    close(fd); // Always close after dup2
}

static char *join_path(const char *dir, const char *cmd)
{
    size_t len_dir = strlen(dir);
    size_t len_cmd = strlen(cmd);
    char *full_path = malloc(len_dir + len_cmd + 2); // +1 for '/' +1 for '\0'
    if (!full_path)
        return NULL;
    strcpy(full_path, dir);
    if (dir[len_dir - 1] != '/')
        strcat(full_path, "/");
    strcat(full_path, cmd);
    return full_path;
}

static char *check_direct_path(char *cmd)
{
    if (strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        else
            return (NULL);
    }
    return (NULL);
}

static char *search_in_path(char *cmd, char *path_env)
{
    char **paths;
    char *full_path;
    int i;

    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        full_path = join_path(paths[i], cmd);
        if (!full_path)
            break;
        if (access(full_path, X_OK) == 0)
        {
            free_tab(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_tab(paths);
    return (NULL);
}

char *get_cmd_path(char *cmd, t_env *env)
{
    char *path_env;

    if (!cmd)
        return (NULL);
    path_env = NULL;
    char *direct = check_direct_path(cmd);
    if (direct)
        return (direct);
    while (env)
    {
        if (ft_strncmp(env->value, "PATH=", 5) == 0)
        {
            path_env = env->value + 5;
            break;
        }
        env = env->next;
    }
    if (!path_env)
        return (NULL);
    return (search_in_path(cmd, path_env));
}
static void handle_child(t_cmd *cmd, t_mini *mini, int prev_pipe, int *pipefd)
{
    // Set up input from previous pipe
    if (prev_pipe != -1)
    {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }

    // ✅ Set up output to next pipe first
    if (cmd->next)
    {
        close(pipefd[0]); // close read-end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }

    // ✅ Then apply redirections (they overwrite STDOUT if needed)
    handle_redirs(cmd->redirections, mini);

    if (!cmd->cmd || !cmd->args || !cmd->args[0])
        exit(EXIT_FAILURE);

    if (is_builtin(cmd->args[0]))
        exit(exec_builtin(cmd->args, mini));

    char *path = get_cmd_path(cmd->args[0], mini->env);
    if (!path)
        exit(127);
    magic_box(path, cmd, mini->env, mini);
}

void exec_pipeline(t_mini *mini)
{
    t_cmd *cmd = mini->start_cmd;
    int prev_pipe = -1;
    int pipefd[2];
    pid_t pid;

    while (cmd)
    {
        // Check if it's a single builtin without pipeline
        if (!cmd->next && is_builtin(cmd->args[0]))
        {
            // ✅ Handle redirection before executing builtin
            int saved_stdout = dup(STDOUT_FILENO);
            int saved_stdin = dup(STDIN_FILENO);

            if (cmd->redirections)
                handle_redirs(cmd->redirections, mini);

            exec_builtin(cmd->args, mini);

            // ✅ Restore stdout and stdin
            dup2(saved_stdout, STDOUT_FILENO);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdout);
            close(saved_stdin);
        }
        else
        {
            if (cmd->next && pipe(pipefd) == -1)
                return (perror("pipe"));

            if ((pid = fork()) == -1)
                return (perror("fork"));

            else if (pid == 0)
                handle_child(cmd, mini, prev_pipe, pipefd);

            if (prev_pipe != -1)
                close(prev_pipe);

            prev_pipe = (cmd->next) ? pipefd[0] : -1;
            if (cmd->next)
                close(pipefd[1]);
        }
        cmd = cmd->next;
    }

    while (wait(NULL) > 0)
        ;
}

void handle_redirs(t_redirections *redir, t_mini *mini)
{
    while (redir)
    {
        if (redir->type == TRUNC || redir->type == APPEND)
            handle_redirection(mini, redir);
        else if (redir->type == INPUT)
            input(mini, redir);
        redir = redir->next;
    }
}

void minishell(t_mini *mini)
{
    t_cmd *cmd;
    int status;

    cmd = mini->start_cmd;
    while (mini->exit == 0 && cmd)
    {
        // mini->charge = 1;
        mini->parent = 1;
        // mini->last = 1;

        exec_pipeline(mini);
        reset_std(mini);
        close_fds(mini);
        reset_fds(mini);

        waitpid(-1, &status, 0);
        status = WEXITSTATUS(status);

        if (mini->parent == 0)
        {
            free_cmd(mini->start_cmd);
            exit(mini->ret);
        }

        mini->no_exec = 0;
        cmd = cmd->next;
    }
}

int main(int ac, char **av, char **env)
{
    t_mini mini;

    (void)ac;
    (void)av;
    // mini.in = dup(n.STDIN);
    // mini.out = dup(n.STDOUT);
    mini.exit = 0;
    mini.ret = 0;
    mini.no_exec = 0;
    reset_fds(&mini);
    env_init(&mini, env);
    secret_env_init(&mini, env);
    while (mini.exit == 0)
    {
        parse(&mini);
        if (mini.start_cmd != NULL)
            minishell(&mini);
    }
    free_env(mini.env);
    free_env(mini.secret_env);
    return (mini.ret);
}
