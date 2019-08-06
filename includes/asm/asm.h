/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 05:01:24 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/30 14:55:56 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include "asm_strings.h"

/*
** ---------- FLAGS ----------
*/

# define F_CHAMP_NAME			(1 << 1)
# define F_CHAMP_COMMENT		(1 << 0)

/*
** ---------- MACROS & DEFINES ----------
*/

# define ABS(a)					((a) > 0 ? (a) : -(a))
# define MAX(a, b)				((a) > (b) ? (a) : (b))
# define MIN(a, b)				((a) < (b) ? (a) : (b))

# define SOURCE_EXT				".s"
# define OUTPUT_EXT				".cor"

# define NULL_SEPARATOR_SIZE	4

# define REG_CHAR				'r'

# define ASM_REG_SIZE			1
# define ASM_IND_SIZE			2

/*
** ---------- OPERATIONS ----------
*/

# define OP_NUMBER				16
# define ARGS_NUMBER			3

typedef enum
{
	false,
	true
}	t_bool;

typedef struct	s_op
{
	char			*name;
	unsigned char	code;
	unsigned char	args_num;
	t_bool			args_types_code;
	t_arg_type		args_types[ARGS_NUMBER];
	unsigned char	t_dir_size;
}				t_op;

/*
** g_op_tab.c
*/
extern const t_op g_op_tab[OP_NUMBER];

/*
** ---------- TYPEDEFS & STRUCTURES ----------
*/

typedef struct	s_label
{
	char			*name;
	int				mem_pos;
}				t_label;

typedef struct	s_arg_label
{
	char			*name;
	int				code_line;
	int				mem_pos;
	int				pos_in_op;
	int				size;
}				t_arg_label;

typedef struct	s_args
{
	int				op_num;
	int				arg_num;
	unsigned char	args_types_code;
	int				arg[ARGS_NUMBER];
	unsigned char	arg_size[ARGS_NUMBER];
}				t_args;

typedef struct	s_asm
{
	char			*source_file;
	int				fd;
	int				line_num;

	unsigned short	flags;

	t_header		header;

	t_label			*label;
	int				label_num;
	t_arg_label		*arg_label;
	int				arg_label_num;
}				t_asm;

/*
** ---------- FUNCTIONS ----------
*/

/*
** free & exit functions (utils.c)
*/
void			success(t_asm *a, const char *format, ...);
void			fail(t_asm *a, const char *format, ...);
void			fail_free_line(t_asm *a, char *line, const char *format, ...);

/*
** utils.c
*/
int				get_line(t_asm *a, char **line);
void			*memrev(void *s, size_t size);

/*
** utils2.c
*/
int				is_comment(char *line);

/*
** handling_header.c
*/
void			handling_header(t_asm *a);

/*
** handling_label.c
*/
int				is_label(t_asm *a, char **line);
void			add_args_label(t_asm *a, t_args *args,
								char **line, char *line_ptr_backup);
void			bind_args_and_labels(t_asm *a);

/*
** handling_args.c
*/
void			handling_args(t_asm *a, t_args *args,
								char *line, char *line_ptr_backup);

/*
** handling_op.c
*/
void			handling_op(t_asm *a);

/*
** output_file.c
*/
void			file_buffer(t_asm *a, char *src, size_t size);
void			file_set_at(t_asm *a, size_t at, char *src, size_t size);
void			file_output(t_asm *a, char *source_file);
void			file_free_buffer(void);

#endif
