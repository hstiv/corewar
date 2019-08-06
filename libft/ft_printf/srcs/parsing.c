/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 11:41:29 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/02 16:48:26 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		flag_characters(t_printf *p, int func_param)
{
	while (1)
	{
		if (*p->format == '#')
			p->f |= F_ALTF;
		else if (*p->format == '0')
			p->f |= F_ZPAD;
		else if (*p->format == '-')
			p->f |= F_LPAD;
		else if (*p->format == ' ')
			p->f |= F_SPC;
		else if (*p->format == '+')
			p->f |= F_SIGN;
		else if (!(func_param &&
			(*p->format == '.' || (*p->format >= '0' && *p->format <= '9'))))
			break ;
		p->format++;
	}
}

static void		width_precision(t_printf *p)
{
	if ((*p->format >= '1' && *p->format <= '9') || *p->format == '*')
	{
		p->f |= F_PAD;
		wildcards(p, 0);
		if (*p->format >= '1' && *p->format <= '9')
			p->width = ft_atoi(p->format);
		while (*p->format >= '0' && *p->format <= '9')
			p->format++;
		wildcards(p, 0);
	}
	if (*p->format == '.' || *p->format == '*')
	{
		p->format++;
		if (*p->format == '.')
			p->format++;
		p->f |= F_PREC;
		wildcards(p, 1);
		if (*p->format >= '0' && *p->format <= '9')
			p->prec = ft_atoi(p->format);
		while (*p->format >= '0' && *p->format <= '9')
			p->format++;
		wildcards(p, 0);
	}
}

static void		length_modifier(t_printf *p)
{
	while (1)
	{
		if (*p->format == 'h' && *(p->format + 1) == 'h')
			p->f |= F_LMHH;
		else if (*p->format == 'h')
			p->f |= F_LMH;
		else if (*p->format == 'l' && *(p->format + 1) == 'l')
			p->f |= F_LMLL;
		else if (*p->format == 'l')
			p->f |= F_LML;
		else if (*p->format == 'L')
			p->f |= F_LMUL;
		else if (*p->format == 'j')
			p->f |= F_LMJ;
		else if (*p->format == 'z')
			p->f |= F_LMZ;
		else
			return ;
		p->format++;
	}
}

static void		conversion_specifier(t_printf *p)
{
	p->cnv = *p->format;
	if (p->cnv == 'd' || p->cnv == 'D' || p->cnv == 'i' ||
		p->cnv == 'o' || p->cnv == 'O' || p->cnv == 'u' ||
		p->cnv == 'U' || p->cnv == 'x' || p->cnv == 'X' ||
		p->cnv == 'b')
		int_print(p);
	else if (p->cnv == 'f' || p->cnv == 'F')
		float_print(p);
	else if (p->cnv == 'c' || p->cnv == 'C' || p->cnv == 's' || p->cnv == 'S')
		str_print(p);
	else if (p->cnv == 'p')
		pointer_print(p);
	else if (p->cnv == 'n')
		out_len_write(p);
	else if (p->cnv == '%')
		percent_print(p);
	else
		non_valid_print(p);
}

void			parse_format(t_printf *p)
{
	p->format++;
	p->f = 0;
	p->width = 0;
	p->prec = 0;
	p->padding = 0;
	flag_characters(p, 0);
	width_precision(p);
	length_modifier(p);
	flag_characters(p, 1);
	conversion_specifier(p);
}
