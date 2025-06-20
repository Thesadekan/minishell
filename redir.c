/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:28 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/16 18:29:36 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void input(t_mini *mini, t_redirections *redir)
{
	if (!redir->value || redir->value[0] == '\0')
	{
		ft_putendl_fd("minishell: input redirection: empty filename", n.STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return;
	}

	ft_putendl_fd(redir->value, n.STDERR);

	ft_close(mini->fdin);
	mini->fdin = open(redir->value, O_RDONLY);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", n.STDERR);
		ft_putstr_fd(redir->value, n.STDERR);
		ft_putendl_fd(": No such file or directory", n.STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return;
	}

	dup2(mini->fdin, n.STDIN);
}
