/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:08:03 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/18 21:42:19 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list			**link;

	if (!alst)
		return ;
	while ((*alst)->next)
	{
		link = alst;
		while ((*link)->next)
			link = &((*link)->next);
		ft_lstdelone(link, del);
	}
	ft_lstdelone(alst, del);
}
