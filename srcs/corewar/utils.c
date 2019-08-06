/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:55:58 by hstiv             #+#    #+#             */
/*   Updated: 2019/07/31 11:24:57 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

#define IMG 21

void				create_image(t_vm *vm)
{
	int					i;
	int					*data;
	int					gb[3];

	vm->mlx->img_carriage = mlx_new_image(vm->mlx->ptr, IMG, IMG);
	data = (int*)mlx_get_data_addr(vm->mlx->img_carriage, gb, gb + 1, gb + 2);
	i = -1;
	while (++i < IMG)
	{
		data[i] = CORR;
		data[IMG * (IMG - 1) + i] = CORR;
		data[IMG * i] = CORR;
		data[IMG * i + (IMG - 1)] = CORR;
	}
}

char				*itoa_base(int value, int base)
{
	char			*s;
	long			n;
	int				sign;
	int				i;

	n = (value < 0) ? -(long)value : value;
	sign = (value < 0 && base == 10) ? -1 : 0;
	i = (sign == -1) ? 2 : 1;
	while ((n /= base) >= 1)
		i++;
	s = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	n = (value < 0) ? -(long)value : value;
	while (i-- + sign)
	{
		s[i] = (n % base < 10) ? n % base + '0' : n % base + 'a' - 10;
		n /= base;
	}
	(i == 0) ? s[i] = '-' : 0;
	return (s);
}

void				add_zero_to_string(char **s1)
{
	char			*s;
	char			*tmp;

	if (ft_strlen(*s1) < 2)
	{
		s = (char *)malloc(sizeof(char) * 3);
		if (s)
		{
			s[0] = '0';
			s[1] = *s1[0];
			s[2] = '\0';
		}
		tmp = *s1;
		*s1 = s;
		free(tmp);
	}
}

int					ch_col(t_vm *vm, int i)
{
	int				err;

	err = vm->colors[(vm->owner[i] - 1) % 4];
	if (vm->owner[i] == 0)
		err = WHITE;
	return (err);
}

void				help_man(int x, int y, t_vm *vm)
{
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x, y, RED, MAN1);
	y += 50;
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x, y,
			(!vm->mlx->now) ? RED : GREEN, MAN2);
	y += 50;
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x, y, RED, MAN3);
	y += 50;
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x, y, RED, MAN4);
	y += 50;
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x, y, RED, MAN5);
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x, y + 50,
			(vm->mlx->x_button % 2) ? GREEN : RED, SAM);
	mlx_string_put(vm->mlx->ptr, vm->mlx->wind, x, y + 100,
			(vm->mlx->c_button % 2) ? GREEN : RED, SMM);
}
