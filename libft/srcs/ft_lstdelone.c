/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:02:51 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/15 20:56:50 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (!alst || !(*alst) || !del)
		return ;
	(*del)((*alst)->content, (*alst)->content_size);
	free((void *)(*alst));
	*alst = NULL;
}
