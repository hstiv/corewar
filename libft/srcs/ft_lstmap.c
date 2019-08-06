/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:30:46 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/15 21:19:03 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*lst_free(t_list *lst)
{
	t_list			*temp;

	while (lst)
	{
		temp = lst->next;
		if (lst->content && lst->content_size)
			free(lst->content);
		free((void *)lst);
		lst = temp;
	}
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list			*begin;
	t_list			*temp;
	t_list			*a;

	if (!lst || !f)
		return (NULL);
	temp = (*f)(lst);
	if (!(a = ft_lstnew(temp->content, temp->content_size)))
		return (NULL);
	begin = a;
	lst = lst->next;
	while (lst)
	{
		temp = (*f)(lst);
		if (!(a->next = ft_lstnew(temp->content, temp->content_size)))
			return (lst_free(begin));
		a = a->next;
		lst = lst->next;
	}
	return (begin);
}
