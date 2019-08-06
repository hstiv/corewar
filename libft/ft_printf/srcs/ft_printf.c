/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 11:20:34 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/15 22:53:36 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	t_printf		p;
	t_printf		*p_ptr;

	p_ptr = &p;
	p.buff_i = 0;
	p.out_len = 0;
	p.fd = 1;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
			parse_format(p_ptr);
		else if (*p.format == '{' && color_check(p_ptr))
			color_print(p_ptr);
		else
			buffer(p_ptr, p.format, 1);
		p.format++;
	}
	va_end(p.ap);
	write(p.fd, p.buff, p.buff_i);
	return (p.out_len);
}

int				ft_dprintf(int fd, const char *format, ...)
{
	t_printf		p;
	t_printf		*p_ptr;

	p_ptr = &p;
	p.buff_i = 0;
	p.out_len = 0;
	p.fd = fd;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
			parse_format(p_ptr);
		else if (*p.format == '{' && color_check(p_ptr))
			color_print(p_ptr);
		else
			buffer(p_ptr, p.format, 1);
		p.format++;
	}
	va_end(p.ap);
	write(p.fd, p.buff, p.buff_i);
	return (p.out_len);
}

int				ft_vprintf(const char *format, va_list ap)
{
	t_printf		p;
	t_printf		*p_ptr;

	p_ptr = &p;
	p.buff_i = 0;
	p.out_len = 0;
	p.fd = 1;
	p.format = (char *)format;
	va_copy(p.ap, ap);
	while (*p.format)
	{
		if (*p.format == '%')
			parse_format(p_ptr);
		else if (*p.format == '{' && color_check(p_ptr))
			color_print(p_ptr);
		else
			buffer(p_ptr, p.format, 1);
		p.format++;
	}
	write(p.fd, p.buff, p.buff_i);
	return (p.out_len);
}

int				ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_printf		p;
	t_printf		*p_ptr;

	p_ptr = &p;
	p.buff_i = 0;
	p.out_len = 0;
	p.fd = fd;
	p.format = (char *)format;
	va_copy(p.ap, ap);
	while (*p.format)
	{
		if (*p.format == '%')
			parse_format(p_ptr);
		else if (*p.format == '{' && color_check(p_ptr))
			color_print(p_ptr);
		else
			buffer(p_ptr, p.format, 1);
		p.format++;
	}
	write(p.fd, p.buff, p.buff_i);
	return (p.out_len);
}
