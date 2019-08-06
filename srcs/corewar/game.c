/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:00:08 by sdiedra           #+#    #+#             */
/*   Updated: 2019/07/28 16:11:23 by sdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

void	new_op(t_vm *vm, t_proc *proc, t_op op_tab[17])
{
	proc->command_type = vm->arena[proc->pos];
	if (proc->command_type < 17 && proc->command_type > 0)
		proc->cycles_to_wait = op_tab[proc->command_type].cycles_wait;
	else
		proc->cycles_to_wait = 0;
}

int		get_pos(int pos, t_op op, unsigned int octet)
{
	int	new_pos;
	int	i;
	int	arg;

	new_pos = pos + 1;
	if (op.coding_byte)
	{
		new_pos += 1;
		i = 0;
		while (i < op.number)
		{
			arg = get_arg(octet, 2, 7 - i * 2);
			new_pos += get_arg_size(arg, op);
			i++;
		}
		return (new_pos % MEM_SIZE);
	}
	i = 0;
	while (i < op.number)
	{
		new_pos += get_arg_size(op.types_arg[i], op);
		i++;
	}
	return (new_pos % MEM_SIZE);
}

void	do_proc(t_vm *vm, t_proc *proc,
				void (*f[17])(t_vm *, t_proc *), t_op op_tab[17])
{
	unsigned int	type;

	if (op_tab[proc->command_type].coding_byte)
	{
		type = vm->arena[(proc->pos + 1) % MEM_SIZE];
		if (arg_check(type, op_tab[proc->command_type]))
		{
			if (check_reg(type, vm->arena, proc->pos + 1,
							op_tab[proc->command_type]))
				proc->pos = get_pos(proc->pos,
								op_tab[proc->command_type], type);
			else
			{
				f[proc->command_type](vm, proc);
				proc->pos = get_pos(proc->pos, op_tab[proc->command_type],
									type);
			}
		}
		else
			proc->pos = get_pos(proc->pos, op_tab[proc->command_type], type);
	}
	else
		f[proc->command_type](vm, proc);
}

void	performe_proc(t_vm *vm, t_proc *head, t_op op_tab[17])
{
	t_proc	*proccess;
	void	(*f[17])(t_vm *, t_proc *);

	proccess = head;
	init_func(f);
	while (proccess)
	{
		if (!proccess->cycles_to_wait)
			new_op(vm, proccess, op_tab);
		if (proccess->cycles_to_wait > 0)
			proccess->cycles_to_wait -= 1;
		if (!proccess->cycles_to_wait && proccess->command_type < 17
			&& proccess->command_type > 0)
			do_proc(vm, proccess, f, op_tab);
		else if (!proccess->cycles_to_wait)
		{
			proccess->pos += 1;
			proccess->pos %= MEM_SIZE;
		}
		proccess = proccess->next;
	}
}

void	play_game(t_vm *vm, t_op op_tab[17])
{
	performe_proc(vm, vm->list_process, op_tab);
	if (!vm->cycles_to_die)
	{
		check_live(vm, &vm->list_process);
		if (vm->l_exec >= NBR_LIVE || vm->checks >= MAX_CHECKS)
		{
			vm->cycles_die -= CYCLE_DELTA;
			vm->checks = 1;
			if (vm->cycles_die <= 0)
			{
				vm->winner = 1;
				vm->cycles++;
			}
		}
		else
			vm->checks += 1;
		vm->cycles_to_die = vm->cycles_die;
		vm->l_exec = 0;
		null_lives(vm->champs, vm->champ_nb);
	}
	if (vm->winner != 1)
		vm->cycles += 1;
	vm->cycles_to_die -= 1;
}
