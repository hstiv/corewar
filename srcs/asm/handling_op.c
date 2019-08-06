/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 04:04:29 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/30 14:26:59 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		op_name(t_asm *a, char **line, char *line_ptr_backup)
{
	int				op_name_len;
	int				i;

	op_name_len = 0;
	while ((*line)[op_name_len] >= 'a' && (*line)[op_name_len] <= 'z')
		op_name_len++;
	i = -1;
	while (++i < OP_NUMBER)
		if (ft_strnequ(*line, g_op_tab[i].name, op_name_len))
			break ;
	if (i >= OP_NUMBER)
		fail_free_line(a, line_ptr_backup, S_ERR_INV_OP, a->line_num);
	return (i);
}

static int		is_op(t_asm *a, char *line, char *line_ptr_backup)
{
	int				i;
	t_args			args;

	ft_bzero(&args, sizeof(args));
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	args.op_num = op_name(a, &line, line_ptr_backup);
	handling_args(a, &args,
		line + ft_strlen(g_op_tab[args.op_num].name), line_ptr_backup);
	a->header.prog_size += 1 + g_op_tab[args.op_num].args_types_code;
	file_buffer(a, (char *)&g_op_tab[args.op_num].code, 1);
	g_op_tab[args.op_num].args_types_code ?
		file_buffer(a, (char *)&args.args_types_code, 1) : 0;
	i = -1;
	while (++i < g_op_tab[args.op_num].args_num)
	{
		a->header.prog_size += args.arg_size[i];
		file_buffer(a, memrev(&args.arg[i], args.arg_size[i]),
			args.arg_size[i]);
	}
	return (1);
}

void			handling_op(t_asm *a)
{
	char			*line;
	char			*line_ptr_backup;

	while (get_line(a, &line))
	{
		line_ptr_backup = line;
		if (is_comment(line))
			;
		else if (is_label(a, &line))
			;
		else if (is_op(a, line, line_ptr_backup))
			;
		else
			fail_free_line(a, line_ptr_backup, S_ERR_SYNTAX, a->line_num);
		free(line_ptr_backup);
	}
	free(line);
	bind_args_and_labels(a);
}
