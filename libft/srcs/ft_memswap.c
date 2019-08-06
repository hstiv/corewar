/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 01:32:43 by ubyrd             #+#    #+#             */
/*   Updated: 2019/05/13 01:38:20 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_memswap(void *pt1, void *pt2, size_t width)
{
	unsigned char	*a;
	unsigned char	*b;
	unsigned char	temp;
	size_t			i;

	if (!pt1 || !pt2 || !width || pt1 == pt2)
		return ;
	a = (unsigned char *)pt1;
	b = (unsigned char *)pt2;
	i = -1;
	while (++i < width)
	{
		temp = *(a + i);
		*(a + i) = *(b + i);
		*(b + i) = temp;
	}
}
