/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_delone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:02:51 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/18 21:12:23 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_btree_delone(t_btree **node, void (*del)(void *, size_t))
{
	if (!node || !(*node) || !del)
		return ;
	(*del)((*node)->content, (*node)->content_size);
	free((void *)(*node));
	*node = NULL;
}
