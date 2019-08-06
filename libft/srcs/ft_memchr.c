/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:21:50 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/12 02:12:46 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ss;

	ss = (unsigned char *)s;
	while (n--)
		if (*(ss++) == (unsigned char)c)
			return ((void *)(ss - 1));
	return (NULL);
}
