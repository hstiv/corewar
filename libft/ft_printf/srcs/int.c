/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:42:59 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/02 18:45:29 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		sign(t_printf *p, char *buff, intmax_t n, int s_len)
{
	int				padding;

	padding = 0;
	if (p->f & F_PAD && p->f & F_LPAD)
		padding = (!n && p->f & F_PREC && !p->prec) ? p->width :
			MAX(0, p->width - s_len);
	else if (p->f & F_PAD && p->f & F_ZPAD && p->width > s_len)
		padding = ((p->f & F_LPAD || p->f & F_PREC) &&
			(p->f & F_PREC || n < 0)) ? 0 : p->width - s_len;
	s_len += (!n && p->f & F_PREC && !p->prec && p->f & F_PAD &&
		!(p->f & F_LPAD)) ? 1 : 0;
	if (!(p->f & F_PAD && !(p->f & F_LPAD) && p->f & F_ZPAD && p->f & F_SIGN))
	{
		if (n < 0)
			*(buff - s_len - padding) = '-';
		else if (p->f & F_SIGN || p->f & F_SPC)
			*(buff - s_len - padding) = p->f & F_SIGN ? '+' : ' ';
	}
	else if (p->f & F_PREC && p->prec < p->width && p->f & F_PAD &&
	!(p->f & F_LPAD) && p->f & F_ZPAD)
		*(buff - s_len) = n < 0 ? '-' : '+';
	else if (p->f & F_PREC && p->prec < p->width && p->f & F_PAD &&
		!(p->f & F_LPAD))
		*(buff - s_len - padding) = n < 0 ? '-' : '+';
}

static void		putnum(t_printf *p, char *buff, char *s, intmax_t n)
{
	p->padding = MAX(0, p->width - (int)ft_strlen(s));
	p->padding = (!n && p->f & F_PREC && !p->prec) ? p->width : p->padding;
	if (p->f & F_PAD && !(p->f & F_LPAD) && p->f & F_ZPAD &&
		p->f & F_SIGN && (!(p->f & F_PREC) || p->prec >= p->width))
	{
		*(buff++) = n < 0 ? '-' : '+';
		s += p->padding ? 0 : 1;
		p->padding -= p->padding ? 1 : 0;
	}
	if (!n && p->f & F_PREC && !p->prec)
		*s = '\0';
	if (p->f & F_PAD && !(p->f & F_LPAD))
	{
		ft_memset((void *)buff, p->f & F_ZPAD && !(p->f & F_PREC) ? '0' : ' ',
			p->padding);
		buff += p->padding;
	}
	ft_strncpy(buff, (!n && p->f & F_PREC && !p->prec) ? " " : s, ft_strlen(s));
	buff += ft_strlen(s);
	if (p->f & F_PAD && p->f & F_LPAD)
	{
		ft_memset((void *)buff, ' ', p->padding);
		buff += p->padding;
	}
	sign(p, buff, n, (int)ft_strlen(s));
}

static void		sign_base(t_printf *p, char *buff, uintmax_t n, int s_len)
{
	int				padding;

	padding = 0;
	if (p->f & F_PAD && p->f & F_LPAD)
	{
		padding = MAX(0, p->width - s_len);
		padding = (!n && p->f & F_PREC && !p->prec) ? p->width - 1 : padding;
	}
	else if (p->f & F_PAD && p->f & F_ZPAD && p->width >= s_len)
		padding = (!(p->f & F_LPAD) && p->f & F_PREC) ? 0 : p->width - s_len;
	if (p->f & F_PNTR || n != 0 || ((n || p->cnv == 'o' || p->cnv == 'O')
		&& p->f & F_PREC && !p->prec && p->f & F_ALTF))
	{
		if (p->f & F_ALTF && (p->cnv == 'x' || p->cnv == 'X'))
			*(buff - s_len - padding + 1) = p->cnv == 'x' ? 'x' : 'X';
		else if (p->f & F_ALTF && (p->cnv == 'o' || p->cnv == 'O'))
			*(buff - s_len - padding) = '0';
	}
}

static void		putnum_base(t_printf *p, char *buff, char *s, uintmax_t n)
{
	p->padding = (!n && p->f & F_PREC && !p->prec) ? p->width - 1 :
		MAX(0, p->width - (int)ft_strlen(s));
	p->padding = (!n && p->f & F_PREC && !p->prec && !(p->f & F_PNTR)) ?
		p->width : p->padding;
	p->padding -= (!n && p->f & F_PREC && !p->prec && p->f & F_ALTF &&
		((p->cnv != 'x' && p->cnv != 'X') || (p->f & F_PNTR &&
		!(p->f & F_LPAD)))) ? 1 : 0;
	((!n && !(p->f & F_PNTR)) && p->f & F_PREC && !p->prec &&
		(!(p->f & F_ALTF) || p->cnv == 'x' || p->cnv == 'X')) ? *s = '\0' : 0;
	if (p->f & F_PAD && !(p->f & F_LPAD))
	{
		ft_memset((void *)buff, p->f & F_ZPAD && !(p->f & F_PREC) ? '0' : ' ',
			p->padding);
		buff += p->padding;
	}
	ft_strncpy(buff, ((!n && !(p->f & F_PNTR)) &&
		p->f & F_PREC && !p->prec) ? " " : s, ft_strlen(s));
	buff += ft_strlen(s);
	if (p->f & F_PAD && p->f & F_LPAD)
	{
		ft_memset((void *)buff, ' ', p->padding - (!n && p->f & F_PNTR &&
		p->f & F_PREC && !p->prec ? 1 : 0));
		buff += p->padding;
	}
	sign_base(p, buff, n, (int)ft_strlen(s));
}

void			int_print(t_printf *p)
{
	char			*buff;
	char			*s;
	intmax_t		n;
	uintmax_t		un;

	if (p->cnv == 'd' || p->cnv == 'D' || p->cnv == 'i')
	{
		if (!(s = int_cast(p, &n)))
			return ;
		if ((buff = ft_strnew(ft_strlen(s) + MAX(p->width, p->prec))))
			putnum(p, buff, s, n);
	}
	else
	{
		if (!(s = int_base_cast(p, &un)))
			return ;
		if ((buff = ft_strnew(ft_strlen(s) + MAX(p->width, p->prec))))
			putnum_base(p, buff, s, un);
	}
	if (buff)
	{
		buffer(p, buff, ft_strlen(buff));
		free((void *)buff);
	}
	free((void *)s);
}
