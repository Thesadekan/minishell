/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:38:22 by ael-boul          #+#    #+#             */
/*   Updated: 2025/05/31 09:38:24 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*space;
	size_t	i;

	i = 0;
	if (!(space = malloc(size * count + 1)))
		return (NULL);
	while (i < count * size + 1)
		space[i++] = '\0';
	return (space);
}
