/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:50:57 by ael-boul          #+#    #+#             */
/*   Updated: 2025/05/30 17:43:42 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t env_size(char *env)
{
	size_t i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return i;
}

static void free_node(t_env *env)
{
	if (!env)
		return;
	if (env->value)
		ft_memdel(env->value);
	ft_memdel(env);
}

int ft_unset_from_env(char *key, t_env **env_ptr)
{
	t_env	*env;
	t_env	*tmp;

	if (!key || !env_ptr || !*env_ptr)
		return (n.SUCCESS);
	env = *env_ptr;
	if (env->value && ft_strncmp(key, env->value, env_size(env->value)) == 0
		&& key[env_size(env->value)] == '\0')
	{
		*env_ptr = env->next;
		free_node(env);
		return (n.SUCCESS);
	}
	while (env && env->next)
	{
		if (env->next->value && ft_strncmp(key, env->next->value,
			env_size(env->next->value)) == 0
			&& key[env_size(env->next->value)] == '\0')
		{
			tmp = env->next->next;
			free_node(env->next);
			env->next = tmp;
			break ;
		}
		env = env->next;
	}
	return (n.SUCCESS);
}

int ft_unset(char **args, t_mini *mini)
{
    int i;

    if (!args[1])
        return (n.SUCCESS);

    i = 1;
    while (args[i])
    {
        ft_unset_from_env(args[i], &(mini->env));
        ft_unset_from_env(args[i], &(mini->secret_env));
        i++;
    }
    return (n.SUCCESS);
}