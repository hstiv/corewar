/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_prec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 02:54:48 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/02 19:26:49 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		whol_add(char *whol)
{
	int				i;

	whol[0] += 1;
	i = 0;
	while (whol[i] >= 10 && i < (OFFSET_SIZE - 1))
	{
		whol[i + 1] += whol[i] / 10;
		whol[i++] %= 10;
	}
}

static void		frac_add(char *frac, int i, int prec)
{
	frac[++i] += 1;
	while (frac[i] >= 10 && --prec > 0)
	{
		frac[i + 1] += frac[i] / 10;
		frac[i++] %= 10;
	}
}

static int		round(char *frac, int i)
{
	if (frac[i] != 5)
		return (0);
	i--;
	while (i > 0)
	{
		if (frac[i] == 0)
			i--;
		else
			return (1);
	}
	return (0);
}

void			float_prec(t_printf *p, t_float_parts *fp)
{
	int		i;
	int		i_temp;
	int		prec_temp;

	i = OFFSET_SIZE - 1;
	prec_temp = p->prec;
	while (fp->frac[i] == 0 && i > 0)
		i--;
	i_temp = --i;
	while (prec_temp-- && i >= -1)
		i--;
	if (i >= 0 && ((fp->whol[0] % 2 != 0 && fp->frac[i] == 5) ||
		fp->frac[i] > 5 || round(fp->frac, i_temp)) && p->prec == 0)
		whol_add(fp->whol);
	else if (i >= 0 && (fp->frac[i] >= 5 || (fp->frac[i + 1] % 2 != 0 &&
		fp->frac[i] == 5)))
	{
		frac_add(fp->frac, i, p->prec);
		if (fp->frac[i_temp] >= 10)
		{
			fp->frac[i_temp] %= 10;
			whol_add(fp->whol);
		}
	}
}
