/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:42:11 by ael-boul          #+#    #+#             */
/*   Updated: 2025/05/31 09:42:12 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = 0;
	dstlen = 0;
	while (src[srclen] != '\0')
		srclen++;
	while (dst[dstlen] != '\0')
		dstlen++;
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	i = 0;
	while (src[i] != '\0' && dstlen + i < dstsize - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (srclen + dstlen);
}
