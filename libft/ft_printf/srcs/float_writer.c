/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_writer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 12:35:25 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/02 16:13:31 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*frac_write(t_float_parts *fp, int i, int prec)
{
	int		j;

	while (fp->s[i])
		i++;
	fp->s[i++] = '.';
	j = fp->frac_size + 1;
	while (!fp->frac[j] && j >= 0)
		j--;
	j--;
	while (j >= 0 && prec--)
		fp->s[i++] = fp->frac[j--] + '0';
	while (prec-- > 0)
		fp->s[i++] = '0';
	return (fp->s);
}

static int		whol_write(t_printf *p, t_float_parts *fp)
{
	int		i;
	int		j;

	i = fp->whol_size - 1;
	j = 0;
	while (!fp->whol[i] && i >= 0)
		i--;
	if (!fp->whol_b)
		fp->s[j++] = fp->sign ? '-' : '0';
	if (fp->sign || p->f & F_SIGN || p->f & F_SPC)
		fp->s[j++] = '0';
	while (i >= 0)
		fp->s[j++] = fp->whol[i--] + '0';
	return (j);
}

void			float_write(t_printf *p, t_float_parts *fp)
{
	int		i;

	p->prec = ft_abs(p->prec);
	fp->s = (p->prec > fp->frac_size) ?
		ft_strnew(p->prec + fp->whol_size + 1)
		: ft_strnew(fp->frac_size + fp->whol_size + 1);
	if (!fp->s)
		return ;
	i = whol_write(p, fp);
	if (p->prec)
		fp->s = frac_write(fp, i, p->prec);
	else if (!p->prec && p->f & F_ALTF)
	{
		while (fp->s[i])
			i++;
		fp->s[i] = '.';
	}
}
