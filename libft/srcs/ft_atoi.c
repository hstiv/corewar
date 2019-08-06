/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 23:26:27 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/21 12:20:16 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	unsigned long long	num;
	int					sign;
	int					dig_count;

	while (*str == '\t' || *str == '\v' || *str == '\n'
		|| *str == '\r' || *str == '\f' || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	num = 0;
	dig_count = 0;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9' && dig_count++ < 19)
		num = (10 * num) + (unsigned long long)(*(str++) - '0');
	if (num > 9223372036854775807 || dig_count > 19)
		return (sign == -1 ? 0 : -1);
	return ((int)(num * sign));
}
