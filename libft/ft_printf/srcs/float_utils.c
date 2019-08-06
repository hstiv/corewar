/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 10:54:45 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/02 16:40:53 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*float_edge(t_printf *p, t_float_parts *fp)
{
	fp->s = ft_strnew(4);
	if (fp->whol_b == -4611686018427387904)
	{
		ft_strcpy(fp->s, p->cnv == 'f' ? "nan" : "NAN");
		p->f &= ~F_SIGN;
		p->f &= ~F_SPC;
	}
	else if (fp->sign || p->f & F_SIGN || p->f & F_SPC)
		ft_strcpy(fp->s, p->cnv == 'f' ? " inf" : " INF");
	else
		ft_strcpy(fp->s, p->cnv == 'f' ? "inf" : "INF");
	p->f &= ~F_ZPAD;
	return (fp->s);
}

static int		numlen(char *num)
{
	int				i;

	i = 0;
	while (i < OFFSET_SIZE && !num[i])
		i++;
	return (OFFSET_SIZE - i);
}

void			float_add(char *dest, char *src)
{
	int		i;
	int		len;

	len = (numlen(dest) > numlen(src)) ? numlen(dest) : numlen(src);
	i = 0;
	while (i < len)
	{
		dest[i] += src[i];
		if (dest[i] >= 10)
		{
			dest[i + 1] += dest[i] / 10;
			dest[i] %= 10;
		}
		i++;
	}
}

void			float_pow(char *s, int n, int power, int *size)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i++ < power)
	{
		j = 0;
		while (j < OFFSET_SIZE && j <= *size)
			s[j++] *= n;
		j = 0;
		while (j < OFFSET_SIZE && j <= *size)
		{
			if (s[j] >= 10)
			{
				s[j + 1] += s[j] / 10;
				s[j] %= 10;
				(*size)++;
			}
			j++;
		}
	}
	*size = j;
}

void			float_mult(char *s, int mult, int *size)
{
	int		i;

	i = 0;
	while (i < OFFSET_SIZE && i <= *size)
		s[i++] *= mult;
	i = 0;
	while (i <= OFFSET_SIZE && i <= *size)
	{
		if (s[i] >= 10)
		{
			s[i + 1] += s[i] / 10;
			s[i] %= 10;
			(*size)++;
		}
		i++;
	}
	*size = i;
}
