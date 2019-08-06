/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:01:39 by ubyrd             #+#    #+#             */
/*   Updated: 2019/05/25 21:08:58 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putwchar(wchar_t c)
{
	if (c <= 0x7F)
		ft_putchar(c);
	else if (c <= 0x7FF)
	{
		ft_putchar((c >> 6) + 0xC0);
		ft_putchar((c & 0x3F) + 0x80);
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar((c >> 12) + 0xE0);
		ft_putchar(((c >> 6) & 0x3F) + 0x80);
		ft_putchar((c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		ft_putchar((c >> 18) + 0xF0);
		ft_putchar(((c >> 12) & 0x3F) + 0x80);
		ft_putchar(((c >> 6) & 0x3F) + 0x80);
		ft_putchar((c & 0x3F) + 0x80);
	}
}
