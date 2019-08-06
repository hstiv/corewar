/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 23:26:27 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/03 02:23:20 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		get_nbr(const char *str, int base, int sign)
{
	unsigned long long	num;
	unsigned long long	buf;

	num = 0;
	while (1)
	{
		buf = num;
		if (*str >= '0' && *str <= (base <= 10 ? (char)(base - 1 + '0') : '9'))
			num = (base * num) + (unsigned long long)(*(str++) - '0');
		else if (base > 10 && *str >= 'A' && *str < (char)(base - 10 + 'A'))
			num = (base * num) + 10 + (unsigned long long)(*(str++) - 'A');
		else if (base > 10 && *str >= 'a' && *str < (char)(base - 10 + 'a'))
			num = (base * num) + 10 + (unsigned long long)(*(str++) - 'a');
		else
			break ;
		if (num > 9223372036854775807 || num < buf)
			return (sign == -1 ? 0 : -1);
	}
	return (sign * num);
}

int				ft_atoi_base(const char *str, int base)
{
	int					sign;

	if (base > 36 || base < 2)
		return (0);
	while (*str == '\t' || *str == '\v' || *str == '\n'
		|| *str == '\r' || *str == '\f' || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (*str == '0')
		str++;
	return (get_nbr(str, base, sign));
}
