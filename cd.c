/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:21:22 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/02 14:05:06 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
	{
		ft_putendl_fd("too many arguments", 2);
		return;
	}
	if (errno == EACCES)
		ft_putstr_fd("permission denied: ", 2);
	else if (errno == ENOENT)
		ft_putstr_fd("No such file or directory: ", 2);
	else if (errno == ENOTDIR)
		ft_putstr_fd("Not a directory: ", 2);
	else
		ft_putstr_fd("error: ", 2); // fallback

	ft_putendl_fd(args[1], 2);
}

int	ft_cd(char **args)
{
	int	cd_ret;

	if (!args[1]) // No argument: invalid per the subject
	{
		ft_putstr_fd("cd: relative or absolute path required\n", n.STDERR);
		return (1);
	}
	cd_ret = chdir(args[1]);
	if (cd_ret < 0)
	{
		print_error(args);
		return (1);
	}
	return (0);
}