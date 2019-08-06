/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_create_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 04:52:01 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/18 22:06:59 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree			*ft_btree_create_node(void const *content, size_t content_size)
{
	t_btree			*a;

	if (!(a = (t_btree *)malloc(sizeof(*a))))
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
	a->left = NULL;
	a->right = NULL;
	return (a);
}
