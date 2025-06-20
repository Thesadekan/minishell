/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:21:01 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/17 15:07:01 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int print_error(int error, const char *arg)
{
	int i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", n.STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", n.STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(n.STDERR, &arg[i], 1);
		i++;
	}
	write(n.STDERR, "\n", 1);
	return (n.ERROR);
}

int env_add(const char *value, t_env *env)
{
	t_env *new;
	t_env *tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (n.SUCCESS);
	}
	if (!(new = malloc(sizeof(t_env))))
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (n.SUCCESS);
}

char *get_env_name(char *dest, const char *src)
{
	int i;
	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < (size_t)n.BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
int is_in_env(t_env *env, char *args)
{
	char var_name[n.BUFF_SIZE];
	char env_name[n.BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (n.SUCCESS);
}
int is_var_exist(t_env *env, const char *arg)
{
	char var_name[n.BUFF_SIZE];
	char env_name[n.BUFF_SIZE];

	get_env_name(var_name, arg);
	while (env)
	{
		if (env->value)
		{
			get_env_name(env_name, env->value);
			if (ft_strcmp(var_name, env_name) == 0)
				return (1); // Exists
		}
		env = env->next;
	}
	return (0); // Not found
}
int change_value(t_env *env, const char *arg)
{
	char var_name[n.BUFF_SIZE];
	char env_name[n.BUFF_SIZE];

	get_env_name(var_name, arg);
	while (env)
	{
		if (env->value)
		{
			get_env_name(env_name, env->value);
			if (ft_strcmp(var_name, env_name) == 0)
			{
				ft_memdel(env->value);
				env->value = ft_strdup(arg);
				return (1); // Successfully updated
			}
		}
		env = env->next;
	}
	return (0); // Not updated
}
void handle_export_var(t_env *env, t_env *secret, const char *arg)
{
	if (is_var_exist(env, arg))
		change_value(env, arg);
	else
		env_add(arg, env);

	if (is_var_exist(secret, arg))
		change_value(secret, arg);
	else
		env_add(arg, secret);
}

int ft_export(char **args, t_env *env, t_env *secret)
{
	int error_type;
	int i;

	if (!args[1])
	{
		print_sorted_env(secret);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '=')
			return (print_error(-3, args[i]));
		error_type = is_valid_env(args[i]);
		if (error_type <= 0)
			return (print_error(error_type, args[i]));
		if (error_type == 1 || error_type == 2)
			handle_export_var(env, secret, args[i]);
		i++;
	}
	return (0);
}
