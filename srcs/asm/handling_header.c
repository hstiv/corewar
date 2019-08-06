/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 03:53:54 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/30 12:04:31 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		read_string(t_asm *a, char **line, int *i, char flag)
{
	int				i_mem;

	while ((*line)[*i] && ((*line)[*i] == ' ' || (*line)[*i] == '\t'))
		(*i)++;
	if ((*line)[*i] != '"')
		fail_free_line(a, *line, S_ERR_LEXICAL, a->line_num);
	i_mem = 0;
	while (1)
	{
		if (!(*line)[++(*i)])
		{
			free(*line);
			*i = 0;
			!get_line(a, line) ? fail_free_line(a, *line,
				S_ERR_SYNTAX, a->line_num) : 0;
		}
		if ((*line)[*i] == '"')
			break ;
		if (flag && i_mem <= PROG_NAME_LENGTH)
			a->header.prog_name[i_mem++] = (*line)[*i];
		else if (i_mem <= COMMENT_LENGTH)
			a->header.comment[i_mem++] = (*line)[*i];
	}
	(*i)++;
	return (i_mem);
}

static int		handle_name(t_asm *a, char **line)
{
	int				i;
	int				i_name;

	i = 0;
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\t'))
		i++;
	if (ft_strncmp(*line + i, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (0);
	i += ft_strlen(NAME_CMD_STRING);
	i_name = read_string(a, line, &i, 1);
	i_name > PROG_NAME_LENGTH ? fail_free_line(a, *line,
		S_ERR_LONG_NAME, PROG_NAME_LENGTH) : 0;
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\t'))
		i++;
	if ((*line)[i] == '\n')
		return (1);
	if (!(*line)[i] || ((*line)[i] && ((*line)[i] != COMMENT_CHAR &&
		(*line)[i] != ALT_COMMENT_CHAR)))
		fail_free_line(a, *line, S_ERR_SYNTAX, a->line_num);
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if ((*line)[i] != '\n')
		fail_free_line(a, *line, S_ERR_SYNTAX, a->line_num);
	return (1);
}

static int		handle_comment(t_asm *a, char **line)
{
	int				i;
	int				i_com;

	i = 0;
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\t'))
		i++;
	if (ft_strncmp(*line + i, COMMENT_CMD_STRING,
		ft_strlen(COMMENT_CMD_STRING)))
		return (0);
	i += ft_strlen(COMMENT_CMD_STRING);
	i_com = read_string(a, line, &i, 0);
	i_com > COMMENT_LENGTH ? fail_free_line(a, *line,
		S_ERR_LONG_COM, COMMENT_LENGTH) : 0;
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\t'))
		i++;
	if ((*line)[i] == '\n')
		return (1);
	if (!(*line)[i] || ((*line)[i] && ((*line)[i] != COMMENT_CHAR &&
		(*line)[i] != ALT_COMMENT_CHAR)))
		fail_free_line(a, *line, S_ERR_SYNTAX, a->line_num);
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if ((*line)[i] != '\n')
		fail_free_line(a, *line, S_ERR_SYNTAX, a->line_num);
	return (1);
}

static void		write_header(t_asm *a)
{
	char			null_separator[NULL_SEPARATOR_SIZE];

	a->header.magic = COREWAR_EXEC_MAGIC;
	file_buffer(a, memrev(&a->header.magic, sizeof(a->header.magic)),
		sizeof(a->header.magic));
	file_buffer(a, a->header.prog_name, PROG_NAME_LENGTH);
	ft_bzero(null_separator, NULL_SEPARATOR_SIZE);
	file_buffer(a, null_separator, NULL_SEPARATOR_SIZE);
	file_buffer(a, memrev(&a->header.prog_size, sizeof(a->header.prog_size)),
		sizeof(a->header.prog_size));
	file_buffer(a, a->header.comment, COMMENT_LENGTH);
	file_buffer(a, null_separator, NULL_SEPARATOR_SIZE);
}

void			handling_header(t_asm *a)
{
	char			*line;

	while (get_line(a, &line))
	{
		if (is_comment(line))
			;
		else if (!(a->flags & F_CHAMP_NAME) && handle_name(a, &line))
			a->flags |= F_CHAMP_NAME;
		else if (!(a->flags & F_CHAMP_COMMENT) && handle_comment(a, &line))
			a->flags |= F_CHAMP_COMMENT;
		else
			break ;
		if (a->flags & F_CHAMP_NAME && a->flags & F_CHAMP_COMMENT)
			break ;
		free(line);
	}
	free(line);
	if (!(a->flags & F_CHAMP_NAME && a->flags & F_CHAMP_COMMENT))
		fail(a, a->line_num ? S_ERR_SYNTAX : S_ERR_EMPTY, a->line_num);
	write_header(a);
}
