/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:37:07 by ael-boul          #+#    #+#             */
/*   Updated: 2025/05/31 09:37:09 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lstnew;

	if (!(lstnew = malloc(sizeof(t_list))))
		return (NULL);
	lstnew->content = content;
	lstnew->next = NULL;
	return (lstnew);
}
