/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_infix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:10:49 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/18 19:15:26 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_btree_apply_infix(t_btree *root, void (*f)(t_btree *))
{
	if (!root || !f)
		return ;
	if (root->left)
		ft_btree_apply_infix(root->left, (*f));
	(*f)(root);
	if (root->right)
		ft_btree_apply_infix(root->right, (*f));
}
