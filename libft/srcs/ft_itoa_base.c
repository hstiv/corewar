/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 03:41:16 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/21 11:41:58 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_and_size(int n, int base, size_t *sign)
{
	int				i;

	if (base > 36 || base < 2)
		return (0);
	if (n < 0)
		*sign = 1;
	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char			*ft_itoa_base(int n, int base)
{
	char			*a;
	size_t			i;
	size_t			sign;
	int				temp;

	sign = 0;
	i = check_and_size(n, base, &sign);
	if (!(a = (char *)malloc(i + sign + 1)))
		return (NULL);
	if (sign)
		*a = '-';
	*(a + i + sign) = '\0';
	while (i--)
	{
		temp = sign ? -(n % base) : (n % base);
		if (temp > 9)
			*(a + i + sign) = 'A' + (char)(temp - 10);
		else
			*(a + i + sign) = '0' + (char)temp;
		n /= base;
	}
	return (a);
}
