/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 22:46:33 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/15 22:46:33 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			buffer(t_printf *p, char *src, int size)
{
	p->out_len += size;
	while (BUFF_SIZE - p->buff_i < size)
	{
		size -= BUFF_SIZE - p->buff_i;
		while (p->buff_i < BUFF_SIZE)
			p->buff[p->buff_i++] = *(src++);
		write(p->fd, p->buff, BUFF_SIZE);
		p->buff_i = 0;
	}
	while (size--)
		p->buff[p->buff_i++] = *(src++);
}

void			padding(t_printf *p, int func_param)
{
	int				padding;

	padding = p->padding;
	if (func_param == 0)
		while (padding--)
			buffer(p, "0", 1);
	else if (func_param == 1)
		while (padding--)
			buffer(p, " ", 1);
}
