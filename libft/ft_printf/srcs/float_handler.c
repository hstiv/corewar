/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 13:16:25 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/02 15:45:28 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			float_whol(t_float_parts *fp, int expn)
{
	int				i;
	char			pow[F_BUFF_SIZE];
	unsigned long	mask;

	if (fp->whol_b == 0)
	{
		float_mult(fp->whol, 0, &(fp->whol_size));
		return ;
	}
	ft_bzero(pow, F_BUFF_SIZE);
	*pow = 1;
	i = (expn < 63) ? expn + 1 : 64;
	if (expn >= 63)
		float_pow(pow, 2, expn - 63, &(fp->whol_size));
	mask = 1;
	while (i-- >= 0)
	{
		if (fp->whol_b & mask)
			float_add(fp->whol, pow);
		float_mult(pow, 2, &(fp->whol_size));
		mask <<= 1u;
	}
}

static int		cnt_frac(t_float_parts *fp, char *pow, int expn, int sign)
{
	int		i;
	int		j;

	i = 0;
	if (sign)
		j = 64 - expn - 1;
	else
	{
		j = 64;
		while (i++ < expn - 1)
			float_mult(fp->frac, 10, &(fp->frac_size));
		float_pow(pow, 5, expn - 1, &(fp->frac_size));
	}
	return (j);
}

void			float_frac(t_float_parts *fp, unsigned expn, int sign)
{
	int				i;
	char			pow[F_BUFF_SIZE];
	unsigned long	mask;

	ft_bzero(pow, F_BUFF_SIZE);
	*pow = 1;
	*(fp->frac) = 1;
	mask = (unsigned long)1 << 63u;
	i = cnt_frac(fp, pow, expn, sign);
	while (i-- >= 0)
	{
		float_mult(pow, 5, &(fp->frac_size));
		float_mult(fp->frac, 10, &(fp->frac_size));
		if (fp->frac_b & mask)
			float_add(fp->frac, pow);
		mask >>= 1u;
	}
}
