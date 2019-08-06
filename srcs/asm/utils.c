/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 06:27:15 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/30 15:16:45 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			success(t_asm *a, const char *format, ...)
{
	va_list			ap;

	if (format)
	{
		va_start(ap, format);
		ft_vdprintf(STDOUT_FILENO, format, ap);
		va_end(ap);
	}
	close(a->fd);
	file_free_buffer();
	exit(EXIT_SUCCESS);
}

void			fail(t_asm *a, const char *format, ...)
{
	va_list			ap;

	if (format)
	{
		va_start(ap, format);
		ft_vdprintf(STDERR_FILENO, format, ap);
		va_end(ap);
	}
	close(a->fd);
	file_free_buffer();
	exit(EXIT_FAILURE);
}

void			fail_free_line(t_asm *a, char *line, const char *format, ...)
{
	va_list			ap;

	if (format)
	{
		va_start(ap, format);
		ft_vdprintf(STDERR_FILENO, format, ap);
		va_end(ap);
	}
	free(line);
	close(a->fd);
	file_free_buffer();
	exit(EXIT_FAILURE);
}

#define BUFF_SIZE		32

int				get_line(t_asm *a, char **line)
{
	char			buff[BUFF_SIZE];
	int				bytes;
	int				offset;
	int				tail;

	if (a->fd <= 2 || !line || !(*line = ft_strnew(0)))
		fail(a, S_ERR_ALLOC);
	offset = 0;
	while (1)
	{
		if ((bytes = read(a->fd, buff, BUFF_SIZE)) == -1)
			fail_free_line(a, *line, S_ERR_READ, a->source_file);
		if (!(*line = realloc(*line, offset + bytes + 2)))
			fail(a, S_ERR_ALLOC);
		ft_memcpy(*line + offset, buff, bytes);
		offset += bytes;
		if (ft_memchr(buff, '\n', bytes) || bytes != BUFF_SIZE)
			break ;
	}
	tail = ft_memchr(buff, '\n', bytes) ?
		bytes - (int)(ft_memchr(buff, '\n', bytes) - (void *)buff) : 0;
	*(*line + offset - tail + (ft_memchr(buff, '\n', bytes) ? 1 : 0)) = '\0';
	lseek(a->fd, 1 - tail, SEEK_CUR);
	bytes != 0 ? a->line_num++ : 0;
	return (bytes != 0);
}

void			*memrev(void *s, size_t size)
{
	unsigned char	*us;
	size_t			i;
	unsigned char	temp;

	us = (unsigned char	*)s;
	i = 0;
	while (size > 0 && size > i)
	{
		temp = us[i];
		us[i] = us[--size];
		us[size] = temp;
		i++;
	}
	return (us);
}
