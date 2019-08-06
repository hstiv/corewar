/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_label.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:23:53 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/30 14:55:18 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define MEM_ALLOC_STEP 0x1f

static void		add_label(t_asm *a, char *name, int size, char *line_ptr_backup)
{
	int				i;

	if (!(a->label_num & MEM_ALLOC_STEP) && !(a->label = realloc(a->label,
		sizeof(t_label) * (a->label_num + MEM_ALLOC_STEP + 1))))
		fail_free_line(a, line_ptr_backup, S_ERR_ALLOC);
	if (!(a->label[a->label_num].name = malloc(size + 1)))
		fail_free_line(a, line_ptr_backup, S_ERR_ALLOC);
	ft_strncpy(a->label[a->label_num].name, name, size);
	a->label[a->label_num].name[size] = '\0';
	a->label[a->label_num].mem_pos = a->header.prog_size;
	i = -1;
	while (++i < a->label_num)
		if (ft_strequ(a->label[a->label_num].name, a->label[i].name))
			fail_free_line(a, line_ptr_backup, S_ERR_LABEL_EXIST,
				a->label[a->label_num].name, a->line_num);
	a->label_num++;
}

int				is_label(t_asm *a, char **line)
{
	int				i;
	int				i_label;

	i = 0;
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\t'))
		i++;
	i_label = 0;
	while (ft_strchr(LABEL_CHARS, *(*line + i + i_label)))
		i_label++;
	if (i_label - i == 0 || (*line)[i + i_label] != LABEL_CHAR)
		return (0);
	add_label(a, *line + i, i_label, *line);
	i += i_label + 1;
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\t'))
		i++;
	if ((*line)[i] == '\n')
		return (1);
	if ((*line)[i] != COMMENT_CHAR && (*line)[i] != ALT_COMMENT_CHAR)
		return ((*line += i) && 0);
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	return (1);
}

void			add_args_label(t_asm *a, t_args *args,
								char **line, char *line_ptr_backup)
{
	int				i_label;

	(*line)++;
	i_label = 0;
	while (ft_strchr(LABEL_CHARS, *(*line + i_label)))
		i_label++;
	if (!(a->arg_label_num & MEM_ALLOC_STEP) &&
		!(a->arg_label = realloc(a->arg_label,
		sizeof(t_arg_label) * (a->arg_label_num + MEM_ALLOC_STEP + 1))))
		fail_free_line(a, line_ptr_backup, S_ERR_ALLOC);
	if (!(a->arg_label[a->arg_label_num].name = malloc(i_label + 1)))
		fail_free_line(a, line_ptr_backup, S_ERR_ALLOC);
	ft_strncpy(a->arg_label[a->arg_label_num].name, *line, i_label);
	a->arg_label[a->arg_label_num].name[i_label] = '\0';
	a->arg_label[a->arg_label_num].code_line = a->line_num;
	a->arg_label[a->arg_label_num].mem_pos = a->header.prog_size;
	a->arg_label[a->arg_label_num].pos_in_op =
		a->header.prog_size + 1 + g_op_tab[args->op_num].args_types_code +
		(args->arg_num > 0 ? args->arg_size[0] : 0) +
		(args->arg_num > 1 ? args->arg_size[1] : 0);
	a->arg_label[a->arg_label_num].size = args->arg_size[args->arg_num];
	a->arg_label_num++;
	*line += i_label;
}

void			bind_args_and_labels(t_asm *a)
{
	int				i;
	int				j;
	int				diff4;
	short			diff2;

	i = -1;
	while (++i < a->arg_label_num)
	{
		j = -1;
		while (++j < a->label_num)
			if (ft_strequ(a->arg_label[i].name, a->label[j].name))
				break ;
		if (j == a->label_num)
			fail(a, S_ERR_LABEL_ARG,
				a->arg_label[i].name, a->arg_label[i].code_line);
		diff4 = a->label[j].mem_pos - a->arg_label[i].mem_pos;
		diff2 = diff4;
		if (a->arg_label[i].size == 4)
			file_set_at(a, a->arg_label[i].pos_in_op, memrev(&diff4, 4), 4);
		else if (a->arg_label[i].size == 2)
			file_set_at(a, a->arg_label[i].pos_in_op, memrev(&diff2, 2), 2);
	}
}
