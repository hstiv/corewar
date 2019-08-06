/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:29:09 by hstiv             #+#    #+#             */
/*   Updated: 2019/05/31 14:29:10 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

int				expose_hook(void *param)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	mlx_destroy_window(mlx->ptr, mlx->wind);
	exit(0);
}

static void		speed_helper(int keycode, t_mlx *mlx)
{
	if (keycode == 123 && mlx->mseconds < 100000)
	{
		mlx->mseconds += 10000;
		mlx->speed -= 1;
	}
	if (mlx->mseconds > 2000000)
	{
		mlx->mseconds = 2000000;
		mlx->speed = 1;
	}
}

static void		speed_change(int keycode, t_mlx *mlx)
{
	if (keycode == 124 && mlx->mseconds > 100000)
	{
		mlx->mseconds -= 100000;
		mlx->speed += 2;
	}
	if (keycode == 123 && mlx->mseconds >= 100000)
	{
		mlx->mseconds += 100000;
		mlx->speed -= 2;
	}
	if (keycode == 124 && mlx->mseconds <= 100000
						&& mlx->mseconds >= 10000)
	{
		mlx->mseconds -= 10000;
		mlx->speed += 1;
	}
	speed_helper(keycode, mlx);
}

int				key_press(int keycode, t_mlx *mlx)
{
	t_vm		*vm;

	vm = mlx->vm;
	speed_change(keycode, mlx);
	if (keycode == 36)
	{
		mlx->now++;
		mlx->speed = 40;
		mlx->mseconds = 0;
	}
	(keycode == 7) ? mlx->x_button++ : 0;
	(keycode == 8) ? mlx->c_button++ : 0;
	if (keycode == 53)
		exit(0);
	if (keycode == 49)
		mlx->pause = (mlx->pause) ? 0 : 1;
	if (keycode == 76)
		mlx->now = 0;
	return (1);
}
