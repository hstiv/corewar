/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 15:47:57 by sdiedra           #+#    #+#             */
/*   Updated: 2019/07/28 15:52:23 by sdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

void	null_lives(t_champ *champs, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		champs[i].lives_in_period = 0;
}

void	kill_proc(t_proc **head, t_proc *ps)
{
	t_proc	*prev;
	t_proc	*curr;

	if (!head || !ps)
		return ;
	curr = *head;
	if (curr == ps)
	{
		(*head) = (*head)->next;
		free(curr);
		return ;
	}
	while (curr && curr != ps)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	prev->next = curr->next;
	free(curr);
}

void	check_live(t_vm *vm, t_proc **head)
{
	t_proc	*curr;
	t_proc	*next;

	if (!head)
		return ;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		if (vm->cycles - curr->live >= vm->cycles_die)
			kill_proc(head, curr);
		curr = next;
	}
	if (*head == NULL)
		vm->winner = 1;
}
