/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 22:36:08 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/30 14:28:38 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define MEM_ALLOC_STEP 0xfff

static char		*g_buffer = NULL;
static size_t	g_buffer_i = 0;

void			file_buffer(t_asm *a, char *src, size_t size)
{
	while (size--)
	{
		if (!(g_buffer_i & MEM_ALLOC_STEP) &&
			!(g_buffer = realloc(g_buffer, g_buffer_i + MEM_ALLOC_STEP + 1)))
			fail(a, S_ERR_ALLOC);
		g_buffer[g_buffer_i++] = *(src++);
	}
}

void			file_set_at(t_asm *a, size_t at, char *src, size_t size)
{
	at += sizeof(a->header.magic) + PROG_NAME_LENGTH + NULL_SEPARATOR_SIZE +
		sizeof(a->header.prog_size) + COMMENT_LENGTH + NULL_SEPARATOR_SIZE;
	while (size--)
		g_buffer[at++] = *(src++);
}

static void		file_set_prog_size(t_asm *a)
{
	char			*prog_size;
	int				offset;
	int				i;

	prog_size = memrev(&a->header.prog_size, sizeof(a->header.prog_size));
	offset = sizeof(a->header.magic) + PROG_NAME_LENGTH + NULL_SEPARATOR_SIZE;
	i = offset - 1;
	while (++i < (int)(offset + sizeof(a->header.prog_size)))
		g_buffer[i] = *(prog_size++);
}

void			file_output(t_asm *a, char *source_file)
{
	int				fd;
	char			*output_file;

	file_set_prog_size(a);
	*ft_strrchr(source_file, '.') = '\0';
	if (!(output_file = ft_strjoin(source_file, OUTPUT_EXT)))
		fail(a, S_ERR_ALLOC);
	if ((fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		fail(a, S_ERR_WRITE, output_file);
	write(fd, g_buffer, g_buffer_i);
	ft_printf(S_WRITE, output_file);
	free(output_file);
	if (close(fd) == -1)
		fail(a, S_ERR_CLOSE, output_file);
}

void			file_free_buffer(void)
{
	g_buffer ? free(g_buffer) : 0;
	g_buffer = NULL;
	g_buffer_i = 0;
}
