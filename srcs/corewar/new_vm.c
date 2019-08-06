/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:19:27 by sdiedra           #+#    #+#             */
/*   Updated: 2019/07/28 15:59:13 by sdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

void			new_vm(t_vm *vm)
{
	ft_memset(vm->arena, 0, MEM_SIZE);
	ft_memset(vm->owner, 0, MEM_SIZE);
	vm->next_champ_numb = 1;
	vm->dump_cycles = -1;
	vm->champ_nb = 0;
	vm->winner = 0;
	vm->cycles = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->cycles_die = CYCLE_TO_DIE;
	vm->l_exec = 0;
	vm->checks = 1;
	vm->list_process = NULL;
	vm->colors[0] = RED;
	vm->colors[1] = YELLOW;
	vm->colors[2] = ORANGE;
	vm->colors[3] = PINK;
	vm->mlx = NULL;
}
