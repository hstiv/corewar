/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 03:37:14 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/02 16:11:12 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>

static void		set_float_parts(t_float_parts *fp, t_float fb)
{
	ft_bzero(fp->whol, F_BUFF_SIZE);
	ft_bzero(fp->frac, F_BUFF_SIZE);
	fp->whol_size = 10;
	fp->frac_size = 10;
	fp->whol_b = fb.bits.mant;
	fp->frac_b = fb.bits.mant;
	fp->sign = (fb.bits.sign) ? 1 : 0;
}

static char		*float_cast(t_printf *p, t_float *f)
{
	t_float_parts	fp;
	int				expn;

	f->f = p->f & F_LMUL ? va_arg(p->ap, long double) :
		(long double)va_arg(p->ap, double);
	set_float_parts(&fp, *f);
	expn = f->bits.expn - 0x3fff;
	if (expn == 0x4000)
		return (float_edge(p, &fp));
	else if (f->f == DBL_MIN || f->f == LDBL_MIN || (expn >= 0 && expn < 0x3f))
	{
		fp.whol_b = f->f == DBL_MIN || f->f == LDBL_MIN ? 0 :
			f->bits.mant >> (64u - (expn + 1u));
		fp.frac_b = f->f == DBL_MIN || f->f == LDBL_MIN ? 0 :
			f->bits.mant << (expn + 1u);
	}
	else if (expn >= 0x3f)
		fp.frac_b = 0;
	else
		fp.whol_b = 0;
	float_whol(&fp, expn);
	float_frac(&fp, expn >= (-1100) ? ABS(expn) : 0, (expn >= 0));
	float_prec(p, &fp);
	float_write(p, &fp);
	return (fp.s);
}

static void		sign(t_printf *p, char *buff, t_float f, int s_len)
{
	int				padding;

	padding = 0;
	if (p->f & F_PAD && p->f & F_LPAD)
		padding = MAX(0, p->width - s_len);
	else if (p->f & F_PAD && p->f & F_ZPAD && p->width > s_len)
		padding = p->width - s_len;
	if (!(p->f & F_PAD && !(p->f & F_LPAD) && p->f & F_ZPAD && p->f & F_SIGN))
	{
		if (f.bits.sign)
			*(buff - s_len - padding) = '-';
		else if (p->f & F_SIGN || p->f & F_SPC)
			*(buff - s_len - padding) = p->f & F_SIGN ? '+' : ' ';
	}
}

static void		putnum(t_printf *p, char *buff, char *s, t_float f)
{
	p->padding = MAX(0, p->width - (int)ft_strlen(s));
	if (*s != 'n' && p->f & F_PAD && !(p->f & F_LPAD) &&
		p->f & F_ZPAD && p->f & F_SIGN)
	{
		*(buff++) = f.bits.sign ? '-' : '+';
		s += p->padding ? 0 : 1;
		p->padding -= p->padding ? 1 : 0;
	}
	if (p->f & F_PAD && !(p->f & F_LPAD))
	{
		ft_memset((void *)buff, p->f & F_ZPAD && *s != 'n' && *s != 'N' ?
			'0' : ' ', p->padding);
		buff += p->padding;
	}
	ft_strncpy(buff, s, ft_strlen(s));
	buff += ft_strlen(s);
	if (p->f & F_PAD && p->f & F_LPAD)
	{
		ft_memset((void *)buff, ' ', p->padding);
		buff += p->padding;
	}
	if (*s != 'n' && *s != 'N')
		sign(p, buff, f, (int)ft_strlen(s));
}

void			float_print(t_printf *p)
{
	char			*buff;
	char			*s;
	t_float			f;

	if (!(p->f & F_PREC))
		p->prec = 6;
	if (!(s = float_cast(p, &f)))
		return ;
	if ((buff = ft_strnew(ft_strlen(s) + MAX(p->width, p->prec))))
		putnum(p, buff, s, f);
	if (buff)
	{
		buffer(p, buff, ft_strlen(buff));
		free((void *)buff);
	}
	free((void *)s);
}
