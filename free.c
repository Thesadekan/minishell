/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:21:59 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/14 16:30:59 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_cmd(t_cmd *start)
{
    t_cmd *tmp;

    while (start)
    {
        tmp = start->next;

        if (start->cmd)
            ft_memdel(start->cmd);

        if (start->args)
            free_tab(start->args); // Assuming args is a NULL-terminated array

        if (start->redirections)
            free_redirections(start->redirections); // You should implement this

        if (start->path)
            ft_memdel(start->path);

        ft_memdel(start);

        start = tmp;
    }
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		ft_memdel(tmp->value);
		ft_memdel(tmp);
	}
	ft_memdel(env->value);
	ft_memdel(env);
}
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_memdel(tab[i]);
		i++;
	}
	if (tab)
		ft_memdel(tab);
}
void free_redirections(t_redirections *redir)
{
    t_redirections *tmp;

    while (redir)
    {
        tmp = redir->next;

        if (redir->value)
            ft_memdel(redir->value);

        ft_memdel(redir); // Free the current node
        redir = tmp;      // Move to the next
    }
}
