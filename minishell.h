#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <dirent.h>
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef struct s_constants
{
	int ERROR;
	int SUCCESS;
	int BUFF_SIZE;
	int EMPTY;
	int PIPE;
	int END;
	int STDIN;
	int STDOUT;
	int STDERR;
	int SKIP;
	int NOSKIP;
	int UNKNOWN_COMMAND;
	int IS_DIRECTORY;

} t_const;
extern t_const n;

typedef enum s_cmd_type
{
	TRUNC,
	APPEND,
	INPUT,
	CMD,
	ARG
} t_cmd_type;

typedef struct s_redirections
{
	t_cmd_type type;
	char *value;
	struct s_redirections *next;
} t_redirections;

typedef struct s_cmd
{
	char *cmd;
	char **args;
	t_redirections *redirections;
	char *path;
	struct s_cmd *next;
} t_cmd;

typedef struct s_env
{
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_sig
{
	int sigint;
	int sigquit;
	int exit_status;
	pid_t pid;
} t_sig;

typedef struct s_mini
{
	t_cmd *start_cmd; // Start of command linked list (new parser output)
	t_env *env;
	t_env *secret_env;
	int in;
	int out;
	int fdin;
	int fdout;
	int pipin;
	int pipout;
	int parent;
	int pid;
	int ret;
	int exit;
	int no_exec;
} t_mini;
// Function declarations
void handle_redirs(t_redirections *redir, t_mini *mini);
char *get_cmd_path(char *cmd, t_env *env);
int magic_box(char *path, t_cmd *cmd, t_env *env, t_mini *mini);
int env_init(t_mini *mini, char **env_array);
void free_env(t_env *env);
int secret_env_init(t_mini *mini, char **env_array);
void print_sorted_env(t_env *secret);
// void redir(t_mini *mini, t_token *token, int type);
int ft_cd(char **args);
char *env_to_str(t_env *lst);
void free_tab(char **tab);
void free_redirections(t_redirections *redir);
void sort_env(char **tab, int env_len);
void exec_pipeline(t_mini *mini);
// static int	print_error(int error, const char *arg);
int env_add(const char *value, t_env *env);
char *get_env_name(char *dest, const char *src);
int is_in_env(t_env *env, char *args);
int is_valid_env(const char *env);
int ft_export(char **args, t_env *env, t_env *secret);
int ft_echo(char **args);
int ft_unset(char **a, t_mini *mini);
size_t env_size(char *env);
int str_env_len(char **env);
int ft_pwd(void);
int ft_env(t_env *env);
size_t size_env(t_env *lst);
void ft_exit(t_mini *mini, char **cmd);
int exec_builtin(char **args, t_mini *mini);
int is_builtin(char *command);
t_cmd *get_tokens(char *line);
t_cmd_type type_arg(char *str);
void input(t_mini *mini, t_redirections *redir);
void reset_fds(t_mini *mini);
void reset_std(t_mini *mini);
void close_fds(t_mini *mini);
void free_cmd(t_cmd *start);
void parse(t_mini *mini);
void ft_close(int fd);
int exec_bin(char **args, t_env *env, t_mini *mini);
extern t_sig g_sig;
#endif // MINISHELL_H
