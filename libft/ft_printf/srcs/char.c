/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:41:24 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/02 17:25:36 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		put_str(t_printf *p)
{
	char			*s;
	int				size;

	s = va_arg(p->ap, char *);
	if (!s)
		s = NULL_STR;
	size = (int)ft_strlen(s);
	size = p->f & F_PREC ? MIN(size, p->prec) : size;
	p->padding = MAX(0, p->width - size);
	if (p->f & F_PAD && !(p->f & F_LPAD))
		padding(p, p->f & F_ZPAD ? 0 : 1);
	buffer(p, s, size);
	if (p->f & F_PAD && p->f & F_LPAD)
		padding(p, 1);
}

static int		calc_size(t_printf *p, wchar_t *s)
{
	int				i;
	int				prec;

	i = 0;
	prec = p->prec;
	while (*s && prec >= 0)
	{
		if ((prec -= ft_wcharlen(*s)) >= 0)
			i += ft_wcharlen(*s);
		s++;
	}
	return (i);
}

static void		buff_wchar(t_printf *p, wchar_t c)
{
	char			buff[4];

	if (c <= 0x7F)
		buff[0] = c;
	else if (c <= 0x7FF)
	{
		buff[0] = (c >> 6) + 0xC0;
		buff[1] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0xFFFF)
	{
		buff[0] = (c >> 12) + 0xE0;
		buff[1] = ((c >> 6) & 0x3F) + 0x80;
		buff[2] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0x10FFFF)
	{
		buff[0] = (c >> 18) + 0xF0;
		buff[1] = ((c >> 12) & 0x3F) + 0x80;
		buff[2] = ((c >> 6) & 0x3F) + 0x80;
		buff[3] = (c & 0x3F) + 0x80;
	}
	buffer(p, buff, ft_wcharlen(c));
}

static void		put_wstr(t_printf *p)
{
	wchar_t			*s;
	int				size;

	s = va_arg(p->ap, wchar_t *);
	if (!s)
		s = L_NULL_STR;
	size = p->f & F_PREC ? calc_size(p, s) : (int)ft_wstrlen(s);
	p->padding = MAX(0, p->width - size);
	if (p->f & F_PAD && !(p->f & F_LPAD))
		padding(p, p->f & F_ZPAD ? 0 : 1);
	while (*s && size > 0)
	{
		if (size >= (int)ft_wcharlen(*s))
			buff_wchar(p, *(s));
		size -= ft_wcharlen(*(s++));
	}
	if (p->f & F_PAD && p->f & F_LPAD)
		padding(p, 1);
}

void			str_print(t_printf *p)
{
	wchar_t			c;

	if (p->cnv == 'c' || p->cnv == 'C')
	{
		c = (p->cnv == 'c' && !(p->f & F_LML)) ?
			(char)va_arg(p->ap, wchar_t) : va_arg(p->ap, wchar_t);
		p->padding = ft_wcharlen(c);
		p->padding = MAX(0, p->width - p->padding);
		if (p->f & F_PAD && !(p->f & F_LPAD))
			padding(p, p->f & F_ZPAD ? 0 : 1);
		buff_wchar(p, c);
		if (p->f & F_PAD && p->f & F_LPAD)
			padding(p, 1);
	}
	else if (p->cnv == 's' && (!(p->f & F_LML) || p->f & F_LMLL))
		put_str(p);
	else
		put_wstr(p);
}
