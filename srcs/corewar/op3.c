/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:23:57 by hstiv             #+#    #+#             */
/*   Updated: 2019/07/28 20:41:41 by sdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

void	op_ldi(t_vm *vm, t_proc *proc)
{
	int		type;
	int		i;
	int		j;
	int		args[3];

	i = -1;
	j = 0;
	while (++i < 2)
	{
		type = get_arg(vm->arena[(proc->pos + 1) % MEM_SIZE], 2, 7 - 2 * i);
		if (type == T_REG)
			args[i] = proc->reg[vm->arena[(proc->pos + 2 + j) % MEM_SIZE] - 1];
		else if (type == T_DIR)
			args[i] = rev_byte(vm, (proc->pos + 2 + j) % MEM_SIZE, 2);
		else
		{
			args[i] = rev_byte(vm, (proc->pos + 2 + j) % MEM_SIZE, 2) % IDX_MOD;
			args[i] = plus_pos(args[i], proc->pos);
			args[i] = rev_byte(vm, args[i], 4);
		}
		j += (type == T_REG) ? 1 : 2;
	}
	args[2] = vm->arena[(proc->pos + 2 + j) % MEM_SIZE] - 1;
	i = rev_byte(vm, (proc->pos + (args[0] + args[1]) % IDX_MOD) % MEM_SIZE, 4);
	proc->reg[args[2]] = i;
}

void	cyc(t_vm *vm, int j, int args[3], t_proc *proc)
{
	int	i;

	i = -1;
	while (++i < REG_SIZE)
	{
		vm->arena[(j + REG_SIZE - i - 1) % MEM_SIZE] = (args[0] >> (i * 8));
		vm->owner[(j + REG_SIZE - i - 1) % MEM_SIZE] = proc->player_id;
	}
}

void	op_sti(t_vm *vm, t_proc *proc)
{
	int		type;
	int		i;
	int		j;
	int		args[3];

	i = -1;
	j = 0;
	while (++i < 3)
	{
		type = get_arg(vm->arena[(proc->pos + 1) % MEM_SIZE], 2, 7 - 2 * i);
		if (type == T_REG)
			args[i] = proc->reg[vm->arena[(proc->pos + 2 + j) % MEM_SIZE] - 1];
		else if (type == T_DIR)
			args[i] = rev_byte(vm, (proc->pos + 2 + j) % MEM_SIZE, 2);
		else
		{
			args[i] = rev_byte(vm, (proc->pos + 2 + j) % MEM_SIZE, 2) % IDX_MOD;
			args[i] = plus_pos(args[i], proc->pos);
			args[i] = rev_byte(vm, args[i], 4);
		}
		j += (type == T_REG) ? 1 : 2;
	}
	j = plus_pos(proc->pos, (args[1] + args[2]) % IDX_MOD);
	cyc(vm, j, args, proc);
}

void	op_fork(t_vm *vm, t_proc *proc)
{
	int arg;
	int	i;

	i = -1;
	arg = rev_byte(vm, (proc->pos + 1) % MEM_SIZE, 2) % IDX_MOD;
	arg = plus_pos(arg, proc->pos);
	proccess_add(&vm->list_process, new_proc(vm->list_process->player_id, arg));
	vm->list_process->carry = proc->carry;
	vm->list_process->live = proc->live;
	while (++i < REG_NUMBER)
		vm->list_process->reg[i] = proc->reg[i];
	proc->pos = (proc->pos + 3) % MEM_SIZE;
}

void	op_lld(t_vm *vm, t_proc *proc)
{
	int	type;
	int	n_pos;
	int	number;

	if ((type = get_arg(vm->arena[(proc->pos + 1) % MEM_SIZE], 2, 7)) == T_DIR)
		n_pos = (proc->pos + 2) % MEM_SIZE;
	else
	{
		n_pos = rev_byte(vm, (proc->pos + 2) % MEM_SIZE, 2);
		n_pos = plus_pos(n_pos, proc->pos);
	}
	number = rev_byte(vm, n_pos, 4);
	if (!number)
		proc->carry = 1;
	else
		proc->carry = 0;
	if (type == T_DIR)
		proc->reg[vm->arena[(proc->pos + 2 + 4) % MEM_SIZE] - 1] = number;
	else
		proc->reg[vm->arena[(proc->pos + 2 + 2) % MEM_SIZE] - 1] = number;
}
