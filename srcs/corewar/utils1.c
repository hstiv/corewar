/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:13:51 by hstiv             #+#    #+#             */
/*   Updated: 2019/07/28 19:13:53 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

char				*get_str(char *s, char *s1)
{
	char			*s2;

	s2 = ft_strjoin(s, s1);
	free(s1);
	return (s2);
}

int					lstcnt(t_proc *lst)
{
	int				i;
	t_proc			*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char				*get_name(t_vm *vm, int i)
{
	int				t;
	char			*s;
	char			*s1;

	t = 0;
	s = (char *)malloc(sizeof(char) * 129);
	while (vm->champs[i].name[t] != '\0')
	{
		s[t] = (char)vm->champs[i].name[t];
		t++;
	}
	s[t] = '\0';
	s1 = ft_strjoin(vm->mlx->ply_man[i], s);
	free(s);
	return (s1);
}

void				put_speed(int x, int y, t_vm *vm)
{
	int				i;
	char			s[100];
	char			*s1;

	i = 0;
	if (vm->mlx->speed > 0)
	{
		while (i < vm->mlx->speed)
			s[i++] = '-';
	}
	s[i] = '\0';
	s1 = ft_strjoin(SPEED, s);
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x, y, GREEN, s1);
	free(s1);
}

void				put_players(int x, int y, t_vm *vm)
{
	int				i;
	char			*s;

	i = 0;
	while (i < vm->champ_nb)
	{
		y += 70;
		s = get_name(vm, i);
		mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x, y, vm->colors[i % 4], s);
		free(s);
		s = get_str(LL, ft_itoa(vm->champs[i].live));
		y += 20;
		mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x + 30, y, WHITE, s);
		free(s);
		s = get_str(LICP, ft_itoa(vm->champs[i].lives_in_period));
		y += 20;
		mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x + 30, y, WHITE, s);
		free(s);
		i++;
	}
	help_man(x, y + 100, vm);
}
