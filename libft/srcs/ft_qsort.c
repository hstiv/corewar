/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 01:41:41 by ubyrd             #+#    #+#             */
/*   Updated: 2019/05/13 01:42:50 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_qsort(void *base, size_t nel, size_t width,
								int (*compar)(const void *, const void *))
{
	unsigned char	*pt;
	size_t			base_size;
	size_t			i;
	size_t			last;

	if (nel == 1 || !base || !nel || !width || !(*compar))
		return ;
	pt = (unsigned char *)base;
	base_size = width * nel;
	ft_memswap((void *)pt, (void *)(pt + width * (nel / 2)), width);
	last = 0;
	i = width;
	while (i < base_size)
	{
		if ((*compar)((const void *)pt, (const void *)(pt + i)) > 0)
		{
			last += width;
			ft_memswap((void *)(pt + last), (void *)(pt + i), width);
		}
		i += width;
	}
	ft_memswap((void *)pt, (void *)(pt + last), width);
	ft_qsort(base, last / width, width, compar);
	ft_qsort((void *)(pt + last + width), nel - last / width - 1,
			width, compar);
}
