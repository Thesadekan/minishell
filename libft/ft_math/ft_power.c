/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:38:08 by ael-boul          #+#    #+#             */
/*   Updated: 2025/05/31 09:38:09 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int		ft_power(int nbr, int pow)
{
	int	res;

	if (pow == 0)
		return (1);
	res = nbr;
	while (pow > 1)
	{
		res *= nbr;
		pow--;
	}
	return (res);
}
