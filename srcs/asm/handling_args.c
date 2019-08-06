/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:05:51 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/31 13:56:04 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		take_reg(t_asm *a, t_args *args,
							char **line, char *line_ptr_backup)
{
	int				i;

	(*line)++;
	args->args_types_code |= REG_CODE << (6 - 2 * args->arg_num);
	args->arg[args->arg_num] = ft_atoi(*line);
	args->arg_size[args->arg_num] = ASM_REG_SIZE;
	i = 0;
	while ((*line)[i] >= '0' && (*line)[i] <= '9')
		i++;
	if (i > 2 || !i || !args->arg[args->arg_num])
		fail_free_line(a, line_ptr_backup, S_ERR_SYNTAX, a->line_num);
	*line += i;
}

static void		take_dir(t_asm *a, t_args *args,
							char **line, char *line_ptr_backup)
{
	int				i;

	(*line)++;
	args->args_types_code |= DIR_CODE << (6 - 2 * args->arg_num);
	args->arg[args->arg_num] = ft_atoi(*line);
	args->arg_size[args->arg_num] = g_op_tab[args->op_num].t_dir_size;
	if (**line == LABEL_CHAR)
	{
		args->arg[args->arg_num] = 0;
		add_args_label(a, args, line, line_ptr_backup);
	}
	else
	{
		if (**line == '-' || **line == '+')
			(*line)++;
		i = 0;
		while ((*line)[i] >= '0' && (*line)[i] <= '9')
			i++;
		!i ? fail_free_line(a, line_ptr_backup, S_ERR_SYNTAX, a->line_num) : 0;
		*line += i;
	}
}

static void		take_ind(t_asm *a, t_args *args,
							char **line, char *line_ptr_backup)
{
	int				i;

	args->args_types_code |= IND_CODE << (6 - 2 * args->arg_num);
	args->arg[args->arg_num] = ft_atoi(*line);
	args->arg_size[args->arg_num] = ASM_IND_SIZE;
	if (**line == LABEL_CHAR)
	{
		args->arg[args->arg_num] = 0;
		add_args_label(a, args, line, line_ptr_backup);
	}
	else
	{
		if (**line == '-' || **line == '+')
			(*line)++;
		i = 0;
		while ((*line)[i] >= '0' && (*line)[i] <= '9')
			i++;
		!i ? fail_free_line(a, line_ptr_backup, S_ERR_SYNTAX, a->line_num) : 0;
		*line += i;
	}
}

static void		take_arg(t_asm *a, t_args *args,
							char **line, char *line_ptr_backup)
{
	if (args->arg_num && **line != ',')
		fail_free_line(a, line_ptr_backup, S_ERR_SYNTAX, a->line_num);
	else if (args->arg_num)
		(*line)++;
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
	if (g_op_tab[args->op_num].args_types[args->arg_num] & T_REG &&
		**line == REG_CHAR)
		take_reg(a, args, line, line_ptr_backup);
	else if (g_op_tab[args->op_num].args_types[args->arg_num] & T_DIR &&
		**line == DIRECT_CHAR)
		take_dir(a, args, line, line_ptr_backup);
	else if (g_op_tab[args->op_num].args_types[args->arg_num] & T_IND)
		take_ind(a, args, line, line_ptr_backup);
	else
		fail_free_line(a, line_ptr_backup, S_ERR_INV_ARG,
			g_op_tab[args->op_num].name, a->line_num);
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
	args->arg_num++;
}

void			handling_args(t_asm *a, t_args *args,
								char *line, char *line_ptr_backup)
{
	int				i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!i && !(g_op_tab[args->op_num].args_types[args->arg_num] & T_DIR &&
		line[i] == DIRECT_CHAR) &&
		!(g_op_tab[args->op_num].args_types[args->arg_num] & T_IND &&
		(line[i] == '-' || line[i] == '+')))
		fail_free_line(a, line_ptr_backup, S_ERR_SYNTAX, a->line_num);
	while (args->arg_num < g_op_tab[args->op_num].args_num)
		take_arg(a, args, &line, line_ptr_backup);
	i = 0;
	if (line[i] == '\n')
		return ;
	if (!line[i] || (line[i] && (line[i] != COMMENT_CHAR &&
		line[i] != ALT_COMMENT_CHAR)))
		fail_free_line(a, line_ptr_backup, S_ERR_SYNTAX, a->line_num);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] != '\n')
		fail_free_line(a, line_ptr_backup, S_ERR_SYNTAX, a->line_num);
}
