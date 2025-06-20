/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:19 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/19 10:03:18 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse(t_mini *mini)
{
	char *line;

	line = readline("minishell> ");
	if (!line)
	{
		mini->exit = 1;
		ft_putendl_fd("exit", n.STDERR);
		return;
	}

	if (*line)
		add_history(line);

	mini->start_cmd = get_tokens(line); // parsed command list
	t_cmd *tmp = mini->start_cmd;
	while (tmp)
		tmp = tmp->next;

	ft_memdel(line);
}
