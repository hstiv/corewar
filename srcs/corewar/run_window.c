/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:11:41 by mwuckert          #+#    #+#             */
/*   Updated: 2019/07/31 10:52:55 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

void				get_x_y(t_dot *n1, t_proc *proc, t_vm *vm)
{
	n1->x = (proc->pos % BIT_LENGTH) * 25 + BEG;
	n1->y = (proc->pos / BIT_LENGTH) * 20 + vm->mlx->ar_y;
}

void				draw_carriage(t_vm *vm)
{
	t_dot			n;
	t_proc			*tmp;

	tmp = vm->list_process;
	while (tmp)
	{
		get_x_y(&n, tmp, vm);
		mlx_put_image_to_window(vm->mlx->ptr, vm->mlx->wind,
			vm->mlx->img_carriage, n.x, n.y);
		tmp = tmp->next;
	}
}

void				draw_arena(t_vm *vm, int *i, int *x, int y)
{
	char			*s;

	while (*i < MEM_SIZE)
	{
		s = itoa_base(vm->arena[*i], 16);
		add_zero_to_string(&s);
		mlx_string_put(vm->mlx->ptr, vm->mlx->wind,
							*x, y, ch_col(vm, *i), s);
		(*x) += 25;
		free(s);
		if ((*i + 1) % BIT_LENGTH == 0)
			break ;
		(*i)++;
	}
}

void				put_man(t_vm *vm)
{
	char			*s;
	int				y;

	y = vm->mlx->man_y;
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, 2000, y,
	(vm->mlx->pause) ? RED : GREEN, (vm->mlx->pause) ? PAUSE : PLAY);
	s = get_str(STR2, ft_itoa(vm->cycles));
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, 1800, y + 50, WHITE, s);
	free(s);
	s = get_str(STR3, ft_itoa(lstcnt(vm->list_process)));
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, 1800, y + 100, WHITE, s);
	free(s);
	s = get_str(CTD, ft_itoa(vm->cycles_to_die));
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, 1800, y + 130, WHITE, s);
	free(s);
	put_speed(1800, y + 190, vm);
	put_players(1800, y + 210, vm);
}

void				putarenainwindow(t_vm *vm)
{
	int				i;
	int				y;
	int				x;

	i = 0;
	y = vm->mlx->ar_y;
	mlx_clear_window(vm->mlx->ptr, vm->mlx->wind);
	put_man(vm);
	draw_carriage(vm);
	while (i < MEM_SIZE)
	{
		x = BEG;
		draw_arena(vm, &i, &x, y);
		y += 20;
		i++;
	}
}
