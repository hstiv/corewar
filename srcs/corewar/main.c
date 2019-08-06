/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:25:29 by sdiedra           #+#    #+#             */
/*   Updated: 2019/07/31 19:32:24 by sdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

void			init_game_run(t_vm *vm)
{
	while (!vm->winner)
	{
		if (vm->cycles == vm->dump_cycles)
		{
			if (!vm->cycles_to_die)
				check_live(vm, &vm->list_process);
			if (vm->winner)
				break ;
			show_dump(vm);
		}
		play_game(vm, vm->op);
	}
	(vm->mlx) ? mlx_destroy_window(vm->mlx->ptr,
					vm->mlx->wind) : 0;
	ft_printf("Contestant %d, \"%s\", has won !\n",
		vm->winner_n, vm->champs[vm->winner_n - 1].name);
	exit(0);
}

int				main_cycle_vizu(t_vm *vm)
{
	if (!vm->mlx->pause && !vm->winner)
	{
		(vm->cycles == vm->dump_cycles) ? show_dump(vm) : 0;
		play_game(vm, vm->op);
		(vm->mlx->now == 1 && vm->mlx->now != 2)
						? 0 : usleep(vm->mlx->mseconds);
		(vm->mlx->now > 1) ? init_game_run(vm) : 0;
	}
	if (vm->winner)
	{
		ft_printf("Contestant %d, \"%s\", has won !\n",
				vm->winner_n, vm->champs[vm->winner_n - 1].name);
		mlx_destroy_window(vm->mlx->ptr, vm->mlx->wind);
		exit(0);
	}
	putarenainwindow(vm);
	return (1);
}

void			introduce_players(t_vm *vm)
{
	int				i;

	i = 0;
	if (vm->champ_nb == 0)
		threw(USAGE);
	ft_printf("Introducing contestants...\n");
	while (i < vm->champ_nb)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",\
		vm->champs[i].n_place, vm->champs[i].exec_code, vm->champs[i].name,
								vm->champs[i].comment);
		i++;
	}
}

static void		vizu(t_vm *vm, t_op *op)
{
	vm->mlx->op = op;
	if (vm->champ_nb == 0)
		threw(USAGE);
	vm->mlx->ptr = mlx_init();
	vm->mlx->wind = mlx_new_window(vm->mlx->ptr, WIDTH, HEIGHT, WIND);
	create_image(vm);
	mlx_hook(vm->mlx->wind, 17, (1L << 17), expose_hook, vm->mlx);
	mlx_hook(vm->mlx->wind, 2, 0, key_press, vm->mlx);
	mlx_hook(vm->mlx->wind, 4, 0, mouse_press, vm->mlx);
	mlx_loop_hook(vm->mlx->ptr, main_cycle_vizu, vm);
	mlx_loop(vm->mlx->ptr);
}

int				main(int c, char **s)
{
	t_vm			vm;
	t_op			op[17];

	ft_bzero(&vm, sizeof(t_vm));
	new_vm(&vm);
	init_op(op);
	if (c == 1)
		threw(USAGE);
	parser(c, s, &vm);
	arena(&vm);
	introduce_players(&vm);
	vm.winner_n = vm.champ_nb;
	vm.op = op;
	if (!vm.mlx)
		init_game_run(&vm);
	else
		vizu(&vm, op);
	exit(0);
}
