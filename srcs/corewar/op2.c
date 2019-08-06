/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:17:13 by hstiv             #+#    #+#             */
/*   Updated: 2019/07/28 20:17:16 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

static void	dirreg(int type, int *j)
{
	if (type == T_DIR)
		*j += 4;
	else if (type == T_REG)
		*j += 1;
	else
		*j += 2;
}

void		op_and(t_vm *vm, t_proc *proc)
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
			args[i] = rev_byte(vm, (proc->pos + 2 + j) % MEM_SIZE, 4);
		else
		{
			args[i] = rev_byte(vm, (proc->pos + 2 + j) % MEM_SIZE, 2) % IDX_MOD;
			args[i] = plus_pos(args[i], proc->pos);
			args[i] = rev_byte(vm, args[i], 4);
		}
		dirreg(type, &j);
	}
	args[2] = vm->arena[(proc->pos + 2 + j) % MEM_SIZE] - 1;
	proc->reg[args[2]] = args[0] & args[1];
	proc->carry = proc->reg[args[2]] ? 0 : 1;
}

void		op_or(t_vm *vm, t_proc *proc)
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
			args[i] = rev_byte(vm, (proc->pos + 2 + j) % MEM_SIZE, 4);
		else
		{
			args[i] = rev_byte(vm, (proc->pos + 2 + j) % MEM_SIZE, 2) % IDX_MOD;
			args[i] = plus_pos(args[i], proc->pos);
			args[i] = rev_byte(vm, args[i], 4);
		}
		dirreg(type, &j);
	}
	args[2] = vm->arena[(proc->pos + 2 + j) % MEM_SIZE] - 1;
	proc->reg[args[2]] = args[0] | args[1];
	proc->carry = proc->reg[args[2]] ? 0 : 1;
}

void		op_xor(t_vm *vm, t_proc *proc)
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
			args[i] = rev_byte(vm, (proc->pos + 2 + j) % MEM_SIZE, 4);
		else
		{
			args[i] = rev_byte(vm, (proc->pos + 2 + j) % MEM_SIZE, 2) % IDX_MOD;
			args[i] = plus_pos(args[i], proc->pos);
			args[i] = rev_byte(vm, args[i], 4);
		}
		dirreg(type, &j);
	}
	args[2] = vm->arena[(proc->pos + 2 + j) % MEM_SIZE] - 1;
	proc->reg[args[2]] = args[0] ^ args[1];
	proc->carry = proc->reg[args[2]] ? 0 : 1;
}

void		op_zjmp(t_vm *vm, t_proc *proc)
{
	int		arg;

	arg = rev_byte(vm, (proc->pos + 1) % MEM_SIZE, 2);
	arg %= IDX_MOD;
	if (proc->carry != 0)
		proc->pos = plus_pos(proc->pos, arg);
	else
		proc->pos = (proc->pos + 3) % MEM_SIZE;
}
