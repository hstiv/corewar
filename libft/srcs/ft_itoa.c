/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 03:41:16 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/13 19:36:38 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	char			*a;
	size_t			i;
	size_t			sign;
	int				temp;

	sign = 0;
	if (n < 0)
		sign = 1;
	temp = n;
	i = 1;
	while (temp /= 10)
		i++;
	if (!(a = (char *)malloc(i + sign + 1)))
		return (NULL);
	if (sign)
		*a = '-';
	*(a + i + sign) = '\0';
	while (i--)
	{
		*(a + i + sign) = '0' + (char)(sign ? -(n % 10) : (n % 10));
		n /= 10;
	}
	return (a);
}
