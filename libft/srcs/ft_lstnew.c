/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 04:52:01 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/15 20:47:13 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list			*a;

	if (!(a = (t_list *)malloc(sizeof(*a))))
		return (NULL);
	if (!content || !content_size)
	{
		a->content = NULL;
		a->content_size = 0;
	}
	else
	{
		if (!(a->content = malloc(content_size)))
		{
			free((void *)a);
			return (NULL);
		}
		a->content = ft_memcpy(a->content, content, content_size);
		a->content_size = content_size;
	}
	a->next = NULL;
	return (a);
}
