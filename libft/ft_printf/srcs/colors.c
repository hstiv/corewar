/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 04:42:32 by ubyrd             #+#    #+#             */
/*   Updated: 2019/05/26 05:38:03 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				color_check(t_printf *p)
{
	if (!ft_strncmp(p->format, "{RES}", 5) ||
		!ft_strncmp(p->format, "{BOLD}", 5) ||
		!ft_strncmp(p->format, "{UNDR}", 5) ||
		!ft_strncmp(p->format, "{WHT}", 5) ||
		!ft_strncmp(p->format, "{RED}", 5) ||
		!ft_strncmp(p->format, "{GRN}", 5) ||
		!ft_strncmp(p->format, "{YEL}", 5) ||
		!ft_strncmp(p->format, "{BLU}", 5) ||
		!ft_strncmp(p->format, "{MAG}", 5) ||
		!ft_strncmp(p->format, "{CYN}", 5) ||
		!ft_strncmp(p->format, "{GRY}", 5) ||
		!ft_strncmp(p->format, "{BG_WHT}", 8) ||
		!ft_strncmp(p->format, "{BG_RED}", 8) ||
		!ft_strncmp(p->format, "{BG_GRN}", 8) ||
		!ft_strncmp(p->format, "{BG_YEL}", 8) ||
		!ft_strncmp(p->format, "{BG_BLU}", 8) ||
		!ft_strncmp(p->format, "{BG_MAG}", 8) ||
		!ft_strncmp(p->format, "{BG_CYN}", 8) ||
		!ft_strncmp(p->format, "{BG_GRY}", 8))
		return (1);
	return (0);
}

static char		*color_str(t_printf *p)
{
	if (!ft_strncmp(p->format, "{RES}", 5))
		return (RES);
	else if (!ft_strncmp(p->format, "{BOLD}", 5))
		return (BOLD);
	else if (!ft_strncmp(p->format, "{UNDR}", 5))
		return (UNDR);
	else if (!ft_strncmp(p->format, "{WHT}", 5))
		return (WHT);
	else if (!ft_strncmp(p->format, "{RED}", 5))
		return (RED);
	else if (!ft_strncmp(p->format, "{GRN}", 5))
		return (GRN);
	else if (!ft_strncmp(p->format, "{YEL}", 5))
		return (YEL);
	else if (!ft_strncmp(p->format, "{BLU}", 5))
		return (BLU);
	else if (!ft_strncmp(p->format, "{MAG}", 5))
		return (MAG);
	else if (!ft_strncmp(p->format, "{CYN}", 5))
		return (CYN);
	else if (!ft_strncmp(p->format, "{GRY}", 5))
		return (GRY);
	else if (!ft_strncmp(p->format, "{BG_WHT}", 8))
		return (BG_WHT);
	return (NULL);
}

void			color_print(t_printf *p)
{
	char			*s;

	if (!(s = color_str(p)))
	{
		if (!ft_strncmp(p->format, "{BG_RED}", 8))
			s = BG_RED;
		else if (!ft_strncmp(p->format, "{BG_GRN}", 8))
			s = BG_GRN;
		else if (!ft_strncmp(p->format, "{BG_YEL}", 8))
			s = BG_YEL;
		else if (!ft_strncmp(p->format, "{BG_BLU}", 8))
			s = BG_BLU;
		else if (!ft_strncmp(p->format, "{BG_MAG}", 8))
			s = BG_MAG;
		else if (!ft_strncmp(p->format, "{BG_CYN}", 8))
			s = BG_CYN;
		else if (!ft_strncmp(p->format, "{BG_GRY}", 8))
			s = BG_GRY;
	}
	buffer(p, s, ft_strlen(s));
	while (*p->format != '}')
		p->format++;
}
