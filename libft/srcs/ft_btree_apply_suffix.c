/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_suffix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:11:57 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/18 19:15:44 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_btree_apply_suffix(t_btree *root, void (*f)(t_btree *))
{
	if (!root || !f)
		return ;
	if (root->left)
		ft_btree_apply_suffix(root->left, (*f));
	if (root->right)
		ft_btree_apply_suffix(root->right, (*f));
	(*f)(root);
}
