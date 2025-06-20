/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:01:36 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/16 18:52:52 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_message(char *path)
{
	DIR *folder;
	int fd;
	int ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", n.STDERR);
	ft_putstr_fd(path, n.STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", n.STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", n.STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", n.STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", n.STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = n.UNKNOWN_COMMAND;
	else
		ret = n.IS_DIRECTORY;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int magic_box(char *path, t_cmd *cmd, t_env *env, t_mini *mini)
{
	char **env_array;
	char *env_str;

	env_str = env_to_str(env);
	env_array = ft_split(env_str, '\n');
	ft_memdel(env_str);
	execve(path, cmd->args, env_array);
	perror("execve failed");
	free_tab(env_array);
	free_cmd(mini->start_cmd);
	exit(EXIT_FAILURE);
}

char *path_join(const char *s1, const char *s2)
{
	char *tmp;
	char *path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char *check_dir(char *bin, char *command)
{
	DIR *folder;
	struct dirent *item;
	char *path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, command) == 0)
			path = path_join(bin, item->d_name);
	}
	closedir(folder);
	return (path);
}

int exec_bin(char **args, t_env *env, t_mini *mini)
{
	int i;
	char **bin;
	char *path = get_cmd_path(args[0], env);
	int ret;
	i = 0;
	ret = n.UNKNOWN_COMMAND;

	// find PATH in env
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;

	if (env == NULL || env->next == NULL)
		return (magic_box(path, mini->start_cmd, env, mini)); // ✅ updated

	bin = ft_split(env->value, ':');
	if (!args[0] && !bin[0])
	{
		free_tab(bin);
		return (n.ERROR);
	}

	i = 1;
	path = check_dir(bin[0] + 5, args[0]);

	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);

	// ✅ set path inside the cmd struct
	if (path != NULL)
	{
		ft_memdel(mini->start_cmd->path);
		mini->start_cmd->path = path;
		ret = magic_box(path, mini->start_cmd, env, mini); // ✅ updated
	}
	else
		ret = magic_box(path, mini->start_cmd, env, mini); // ✅ updated

	free_tab(bin);
	ft_memdel(path); // free again just in case it wasn't copied
	return (ret);
}
