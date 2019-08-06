/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corvm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 14:27:47 by sdiedra           #+#    #+#             */
/*   Updated: 2019/07/31 10:39:33 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORVM_H
# define CORVM_H

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <mlx.h>
# include <math.h>

# define BUFF_SIZE	32
# define USAGE		"Usage: ./corewar [-dump [nbr_cycles]] " USAGE1
# define USAGE1		"[-n [number]] [-vi] champion.cor ...\n"
# define HEIGHT		1395
# define WIDTH		2560
# define BEG		40
# define STR2		"Cycles :  "
# define STR3		"Processes :  "
# define PAUSE		"** PAUSED **"
# define PLAY		"** RUNNING **"
# define PLYR1		"PLAYER -1 :  "
# define PLYR2		"PLAYER -2 :  "
# define PLYR3		"PLAYER -3 :  "
# define PLYR4		"PLAYER -4 :  "
# define LL			"Last live :               "
# define LICP		"Live in current period :  "
# define CTD		"CYCLE_TO_DIE :  "
# define SPEED		"Speed :  "
# define MAN1		"Speed manipulation :               [< / >]"
# define MAN2		"Max speed :                   [Return] X 1"
# define MAN3		"Max speed cancellation :           [Enter]"
# define MAN4		"Exit with result :            [Return] X 2"
# define MAN5		"Exit without result :                [Esc]"
# define SAM		"Scroll Arena mode :             [X button]"
# define SMM		"Scroll Manual mode :            [C button]"
# define WHITE		16777215
# define GREEN		65280
# define RED		16711680
# define YELLOW		65525
# define ORANGE		16682752
# define PINK		16715426
# define CORR		GREEN
# define BIT_LENGTH	64
# define WIND		"Corewar: Angel Arena"

typedef struct	s_dot
{
	int				x;
	int				y;
}				t_dot;

typedef struct	s_mlx
{
	void			*wind;
	void			*ptr;
	void			*img_carriage;
	useconds_t		mseconds;
	int				memsize;
	int				pause;
	int				err;
	int				derr;
	void			*vm;
	void			*op;
	int				now;
	char			*ply_man[4];
	int				speed;
	int				man_y;
	int				ar_y;
	int				x_button;
	int				c_button;
}				t_mlx;

typedef struct	s_proc
{
	int				carry;
	unsigned int	reg[REG_NUMBER];
	int				pos;
	int				player_id;
	int				cycles_to_wait;
	int				live;
	int				command_type;
	struct s_proc	*next;
}				t_proc;

typedef struct	s_champ
{
	unsigned char	name[PROG_NAME_LENGTH + 1];
	unsigned char	champ_bin[CHAMP_MAX_SIZE];
	unsigned char	comment[COMMENT_LENGTH + 1];
	int				magic;
	int				n_flag;
	int				n_place;
	int				exec_code;
	int				pos;
	int				live;
	int				lives_in_period;
}				t_champ;

typedef struct	s_op
{
	char			*name;
	int				number;
	unsigned char	types_arg[3];
	int				opcode;
	int				cycles_wait;
	char			*description;
	int				coding_byte;
	int				is_short_dir;
}				t_op;

typedef struct	s_vm
{
	int				dump_cycles;
	int				champ_nb;
	t_champ			champs[MAX_PLAYERS];
	t_proc			*list_process;
	unsigned char	arena[MEM_SIZE];
	unsigned char	owner[MEM_SIZE];
	int				next_champ_numb;
	int				cycles;
	int				cycles_to_die;
	int				cycles_die;
	int				winner;
	int				winner_n;
	int				checks;
	int				l_exec;
	int				colors[4];
	t_op			*op;
	t_mlx			*mlx;
}				t_vm;

void			introduce_players(t_vm *vm);
void			init_func(void (*f[17])(t_vm *, t_proc *));
int				ischamp(char *s);
void			is_dump_flag(t_vm *vm, char **av, int c, int *i);
int				is_nflag(char **s, int *i, int c);
void			null_lives(t_champ *champs, int count);
int				get_arg_size(int arg_type, t_op op);
int				arg_check(unsigned char octet, const t_op op);
int				check_reg(unsigned int octet,
						unsigned char arena[MEM_SIZE], int pos, t_op op);
int				cor_sort(t_vm *vm);
void			init_op(t_op op_tab[17]);
void			show_dump(t_vm *vm);
void			play_game(t_vm *vm, t_op op_tab[17]);
void			arena(t_vm *vm);
int				rev_byte(t_vm *vm, unsigned int pc, int nbytes);
int				ft_isdigit_s(char *s);
void			parser(int c, char **s, t_vm *vm);
void			threw(char *s);
void			parse_champs(t_vm *vm, char *name, int n, int number);
void			new_vm(t_vm *vm);
void			check_live(t_vm *vm, t_proc **head);
void			op_live(t_vm *vm, t_proc *proc);
void			op_ld(t_vm *vm, t_proc *proc);
void			op_st(t_vm *vm, t_proc *proc);
void			op_add(t_vm *vm, t_proc *proc);
void			op_sub(t_vm *vm, t_proc *proc);
void			op_and(t_vm *vm, t_proc *proc);
void			op_or(t_vm *vm, t_proc *proc);
void			op_xor(t_vm *vm, t_proc *proc);
void			op_zjmp(t_vm *vm, t_proc *proc);
void			op_ldi(t_vm *vm, t_proc *proc);
void			op_sti(t_vm *vm, t_proc *proc);
void			op_fork(t_vm *vm, t_proc *proc);
void			op_lld(t_vm *vm, t_proc *proc);
void			op_lldi(t_vm *vm, t_proc *proc);
void			op_lfork(t_vm *vm, t_proc *proc);
void			op_aff(t_vm *vm, t_proc *proc);
int				get_arg(int octet, int k, int p);
void			proccess_add(t_proc **head, t_proc *new_p);
t_proc			*new_proc(int player_id, int pos);
int				plus_pos(int i, int j);
void			create_image(t_vm *vm);
void			draw_arena(t_vm *vm, int *i, int *x, int y);
int				ch_col(t_vm *vm, int i);
void			eat_vizu(t_vm *vm);
int				main_cycle_vizu(t_vm *vm);
void			get_x_y(t_dot *n1, t_proc *champ, t_vm *vm);
void			draw_carriage(t_vm *vm);
void			add_zero_to_string(char **s);
void			putarenainwindow(t_vm *vm);
char			*itoa_base(int num, int base);
void			init_mlx_args(t_vm *vm);
int				expose_hook(void *param);
int				key_press(int keycode, t_mlx *param);
void			put_man(t_vm *vm);
int				lstcnt(t_proc *lst);
char			*get_str(char *s, char *s1);
void			put_players(int x, int y, t_vm *vm);
char			*get_name(t_vm *vm, int i);
void			put_speed(int x, int y, t_vm *vm);
void			help_man(int x, int y, t_vm *vm);
int				mouse_press(int keycode, int x, int y, t_mlx *mlx);

#endif
