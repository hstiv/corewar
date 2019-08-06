/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:09:00 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/02 18:24:16 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			wildcards(t_printf *p, int func_param)
{
	if (*(p->format) == '*')
	{
		if (!func_param)
		{
			p->width = (int)va_arg(p->ap, int);
			if (p->width < 0)
			{
				p->width = ABS(p->width);
				p->f |= F_LPAD;
			}
		}
		else if (func_param == 1)
		{
			p->prec = (int)va_arg(p->ap, int);
			if (p->prec < 0)
			{
				p->prec = 0;
				p->f &= ~F_PREC;
			}
		}
		p->format++;
	}
}

void			pointer_print(t_printf *p)
{
	p->f |= F_PNTR;
	p->f |= F_ALTF;
	p->f |= F_LML;
	p->cnv = 'x';
	int_print(p);
}

void			out_len_write(t_printf *p)
{
	int				*n;

	if (!(n = (int *)va_arg(p->ap, int *)))
		return ;
	*n = p->out_len;
}

void			percent_print(t_printf *p)
{
	p->padding = MAX(1, p->width) - 1;
	if (p->f & F_PAD && !(p->f & F_LPAD))
		padding(p, p->f & F_ZPAD ? 0 : 1);
	buffer(p, "%", 1);
	if (p->f & F_PAD && p->f & F_LPAD)
		padding(p, 1);
}

void			non_valid_print(t_printf *p)
{
	p->padding = MAX(1, p->width) - 1;
	if (p->f & F_PAD && !(p->f & F_LPAD))
		padding(p, p->f & F_ZPAD ? 0 : 1);
	if (ft_isprint(*p->format))
		buffer(p, p->format, 1);
	if (p->f & F_PAD && p->f & F_LPAD)
		padding(p, 1);
	if (!*p->format)
		p->format--;
}
