/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:15:37 by sdiedra           #+#    #+#             */
/*   Updated: 2019/07/28 20:21:59 by sdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

void			parse_champs_arg(t_vm *vm, char **s, int i)
{
	int	cc;

	if (vm->champ_nb == MAX_PLAYERS)
		threw(USAGE);
	cc = 0;
	while (cc < vm->champ_nb)
	{
		if (vm->champs[cc].n_place == vm->next_champ_numb)
			vm->next_champ_numb += 1;
		cc++;
	}
	parse_champs(vm, s[i], vm->champ_nb, vm->next_champ_numb);
	vm->champs[vm->champ_nb].n_flag = 0;
	vm->champ_nb += 1;
	vm->next_champ_numb += 1;
}

void			cycle(t_vm *vm, int c, int n)
{
	int	cc;
	int	j;

	cc = c;
	j = 0;
	if (vm->champs[cc].n_flag == 1)
		return ;
	while (cc < vm->champ_nb)
	{
		if (vm->champs[cc].n_place == n)
			vm->champs[cc].n_place++;
		if (vm->champs[cc].n_place ==
			(vm->champs[c].n_place + j) && vm->champs[cc].n_flag)
			j++;
		cc++;
	}
	vm->champs[c].n_place += j;
}

void			cycle1(t_vm *vm, int c, int n)
{
	int	cc;
	int	j;

	cc = 0;
	j = 0;
	if (vm->champs[c].n_flag == 1)
		return ;
	while (cc < c)
	{
		if (vm->champs[cc].n_place == n)
			j++;
		cc++;
	}
	vm->champs[c].n_place += j;
}

void			parse_n_flag(int n, t_vm *vm)
{
	int	cc;

	if (vm->champ_nb == MAX_PLAYERS)
		threw(USAGE);
	cc = -1;
	while (++cc < vm->champ_nb)
		if (vm->champs[cc].n_flag == 1 && n == vm->champs[cc].n_place)
			threw(USAGE);
	if (n == vm->next_champ_numb)
		vm->next_champ_numb += 1;
	else if (n < vm->next_champ_numb)
	{
		cc = -1;
		while (++cc < vm->next_champ_numb + 1)
			cycle(vm, cc, n);
		cc = 0;
		while (cc < vm->champ_nb)
		{
			cycle1(vm, cc, vm->champs[cc].n_place);
			cc++;
		}
		vm->next_champ_numb += 1;
	}
}

void			parser(int c, char **s, t_vm *vm)
{
	int				i;
	int				n;

	i = 1;
	while (i < c)
	{
		if (!ft_strcmp("-dump", s[i]))
			is_dump_flag(vm, s, c, &i);
		else if (ischamp(s[i]))
			parse_champs_arg(vm, s, i);
		else if ((n = is_nflag(s, &i, c)) != 0)
		{
			parse_n_flag(n, vm);
			parse_champs(vm, s[i], vm->champ_nb, n);
			vm->champs[vm->champ_nb].n_flag = 1;
			vm->champ_nb += 1;
		}
		else if (!ft_strcmp("-vi", s[i]))
			eat_vizu(vm);
		else
			threw(USAGE);
		i++;
	}
	(!cor_sort(vm)) ? threw("Error: Wrong [[-n] value]\n") : 0;
}
