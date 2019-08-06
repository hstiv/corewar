/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:16:32 by hstiv             #+#    #+#             */
/*   Updated: 2019/07/28 20:16:37 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

void	op_live(t_vm *vm, t_proc *proc)
{
	int			number;

	number = rev_byte(vm, (proc->pos + 1) % MEM_SIZE, 4);
	proc->live = vm->cycles;
	if (-number > 0 && -number <= vm->champ_nb)
	{
		vm->winner_n = vm->champs[-number - 1].n_place;
		vm->champs[-number - 1].lives_in_period++;
		vm->champs[-number - 1].live = vm->cycles;
	}
	proc->pos += 5;
	proc->pos %= MEM_SIZE;
	vm->l_exec += 1;
}

void	op_ld(t_vm *vm, t_proc *proc)
{
	int	type;
	int	n_pos;
	int	number;

	if ((type = get_arg(vm->arena[(proc->pos + 1) % MEM_SIZE], 2, 7)) == T_DIR)
		n_pos = (proc->pos + 2) % MEM_SIZE;
	else
	{
		n_pos = rev_byte(vm, (proc->pos + 2) % MEM_SIZE, 2) % IDX_MOD;
		n_pos = plus_pos(proc->pos, n_pos);
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

void	op_st(t_vm *vm, t_proc *proc)
{
	int		type;
	int		number;
	int		index;
	int		i;

	number = proc->reg[vm->arena[(proc->pos + 2) % MEM_SIZE] - 1];
	type = get_arg(vm->arena[(proc->pos + 1) % MEM_SIZE], 2, 5);
	if (type == T_REG)
		proc->reg[vm->arena[(proc->pos + 3) % MEM_SIZE] - 1] = number;
	else
	{
		index = rev_byte(vm, (proc->pos + 3) % MEM_SIZE, 2) % IDX_MOD;
		index = plus_pos(index, proc->pos);
		i = -1;
		while (++i < REG_SIZE)
		{
			vm->arena[(index + REG_SIZE
						- i - 1) % MEM_SIZE] = (number >> (i * 8));
			vm->owner[(index + REG_SIZE
						- i - 1) % MEM_SIZE] = proc->player_id;
		}
	}
}

void	op_add(t_vm *vm, t_proc *proc)
{
	int	first;
	int second;
	int	res;

	first = proc->reg[vm->arena[(proc->pos + 2) % MEM_SIZE] - 1];
	second = proc->reg[vm->arena[(proc->pos + 3) % MEM_SIZE] - 1];
	res = first + second;
	proc->reg[vm->arena[(proc->pos + 4) % MEM_SIZE] - 1] = res;
	if (!res)
		proc->carry = 1;
	else
		proc->carry = 0;
}

void	op_sub(t_vm *vm, t_proc *proc)
{
	int	first;
	int second;
	int	res;

	first = proc->reg[vm->arena[(proc->pos + 2) % MEM_SIZE] - 1];
	second = proc->reg[vm->arena[(proc->pos + 3) % MEM_SIZE] - 1];
	res = first - second;
	proc->reg[vm->arena[(proc->pos + 4) % MEM_SIZE] - 1] = res;
	if (!res)
		proc->carry = 1;
	else
		proc->carry = 0;
}
