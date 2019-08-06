/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_prefix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:08:16 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/18 22:37:42 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_btree_apply_prefix(t_btree *root, void (*f)(t_btree *))
{
	if (!root || !f)
		return ;
	(*f)(root);
	if (root->left)
		ft_btree_apply_prefix(root->left, (*f));
	if (root->right)
		ft_btree_apply_prefix(root->right, (*f));
}
