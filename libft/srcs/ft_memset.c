/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:00:01 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/12 02:12:01 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bb;

	bb = (unsigned char *)b;
	while (len--)
		*(bb++) = (unsigned char)c;
	return (b);
}
