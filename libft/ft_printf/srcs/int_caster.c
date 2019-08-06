/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:08:59 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/02 18:28:34 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*itoa_printf(t_printf *p, intmax_t n)
{
	char			*s;
	int				i;
	intmax_t		temp;

	temp = n;
	i = 1;
	while (temp /= 10)
		i++;
	i = MAX(p->prec, i);
	i += n < 0 || p->f & F_SIGN || p->f & F_SPC ? 1 : 0;
	if (!(s = (char *)malloc(i + 1)))
		return (NULL);
	*(s + i) = '\0';
	while (i--)
	{
		*(s + i) = '0' + ((n < 0) ? -(n % 10) : (n % 10));
		n /= 10;
	}
	return (s);
}

char			*int_cast(t_printf *p, intmax_t *n)
{
	char			*s;

	if (p->f < F_LMZ || p->cnv == 'D')
		*n = p->cnv == 'D' ? va_arg(p->ap, intmax_t) :
			(intmax_t)va_arg(p->ap, int);
	else if (p->f & F_LMJ)
		*n = va_arg(p->ap, intmax_t);
	else if (p->f & F_LMZ)
		*n = (intmax_t)va_arg(p->ap, ssize_t);
	else if (p->f & F_LML || p->f & F_LMLL)
		*n = (p->f & F_LMLL) ? (intmax_t)va_arg(p->ap, long long) :
			(intmax_t)va_arg(p->ap, long);
	else if (p->f & F_LMH || p->f & F_LMHH)
		*n = (p->f & F_LMHH) ? (intmax_t)((char)va_arg(p->ap, int)) :
			(intmax_t)((short)va_arg(p->ap, int));
	s = itoa_printf(p, *n);
	return (s);
}

static char		*itoa_base_printf(t_printf *p, uintmax_t n, int base)
{
	char			*s;
	int				i;
	uintmax_t		temp;

	temp = n;
	i = (!n && p->f & F_PNTR && p->f & F_PREC && !p->prec) ? 0 : 1;
	while (temp /= base)
		i++;
	i = n && p->f & F_ALTF && (p->cnv == 'o' || p->cnv == 'O') ?
		MAX(p->prec - 1, i) : MAX(p->prec, i);
	if ((p->cnv == 'x' || p->cnv == 'X' || p->cnv == 'o' || p->cnv == 'O')
		&& p->f & F_ALTF && (n || p->f & F_PNTR))
		i += (p->cnv == 'x' || p->cnv == 'X') ? 2 : 1;
	if (!(s = (char *)malloc(i + 1)))
		return (NULL);
	*(s + i) = '\0';
	while (i--)
	{
		if ((temp = n % base) > 9)
			*(s + i) = ((p->cnv == 'x') ? 'a' : 'A') + (temp - 10);
		else
			*(s + i) = '0' + temp;
		n /= base;
	}
	return (s);
}

char			*int_base_cast(t_printf *p, uintmax_t *n)
{
	char				*s;
	int					base;

	if (p->f < F_LMZ || p->cnv == 'U' || p->cnv == 'O')
		*n = (p->cnv == 'U' || p->cnv == 'O') ?
			va_arg(p->ap, uintmax_t) :
			(uintmax_t)va_arg(p->ap, unsigned);
	else if (p->f & F_LMJ)
		*n = va_arg(p->ap, uintmax_t);
	else if (p->f & F_LMZ)
		*n = (uintmax_t)va_arg(p->ap, ssize_t);
	else if (p->f & F_LML || p->f & F_LMLL)
		*n = (p->f & F_LMLL) ? (uintmax_t)va_arg(p->ap, unsigned long long) :
			(uintmax_t)va_arg(p->ap, unsigned long);
	else if (p->f & F_LMH || p->f & F_LMHH)
		*n = (p->f & F_LMHH) ? (uintmax_t)((unsigned char)va_arg(p->ap, int)) :
			(uintmax_t)((unsigned short)va_arg(p->ap, int));
	if (p->cnv == 'o' || p->cnv == 'O')
		base = 8;
	else if (p->cnv == 'x' || p->cnv == 'X')
		base = 16;
	else
		base = p->cnv == 'b' ? 2 : 10;
	s = itoa_base_printf(p, *n, base);
	return (s);
}
