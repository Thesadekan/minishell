/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:21:43 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/02 22:48:34 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_mini *mini, char **cmd)
{
    int status;
    ft_putstr_fd("exit\n", n.STDERR);

    if (cmd[1] && cmd[2])
    {
        mini->ret = 1;
        ft_putendl_fd("minishell: exit: too many arguments", n.STDERR);
        return;
    }

    if (cmd[1])
    {
        if (ft_strisnum(cmd[1]) == 0)
        {
            mini->ret = 2;
            ft_putstr_fd("minishell: exit: ", n.STDERR);
            ft_putstr_fd(cmd[1], n.STDERR);
            ft_putendl_fd(": numeric argument required", n.STDERR);
            exit(mini->ret);
        }
        status = ft_atoi(cmd[1]) % 256;
    }
    else
    {
        status = 0;
    }

    mini->ret = status;
    
    free_env(mini->env);
   free_env(mini->secret_env);
    
    exit(mini->ret);
}