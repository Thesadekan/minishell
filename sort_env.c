/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:21:36 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/15 16:13:21 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sort_env(char **tab, int env_len)
{
	int ordered;
	int i;
	char *tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

char *env_to_str(t_env *lst)
{
	char *env;
	int i;
	int j;

	if (!(env = malloc(sizeof(char) * size_env(lst) + 1)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}
void print_sorted_env(t_env *env)
{
	int i;
	char **tab;
	char *str_env;

	i = 0;
	str_env = env_to_str(env);
	tab = ft_split(str_env, '\n');
	ft_memdel(str_env);
	sort_env(tab, str_env_len(tab));

	while (tab[i])
	{
		ft_putstr("declare -x ");
		char *equal_sign = ft_strchr(tab[i], '=');
		if (equal_sign)
		{
			int name_len = equal_sign - tab[i];
			write(1, tab[i], name_len); // Print VAR
			ft_putstr("=\"");
			ft_putstr(equal_sign + 1); // Print value
			ft_putendl("\"");
		}
		else
		{
			ft_putendl(tab[i]); // Just VAR
		}
		i++;
	}
	free_tab(tab);
}

int is_valid_env(const char *env)
{
	int i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}
