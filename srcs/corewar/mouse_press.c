/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:04:36 by hstiv             #+#    #+#             */
/*   Updated: 2019/07/28 19:04:41 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

int					mouse_press(int keycode, int x, int y, t_mlx *mlx)
{
	x = 0;
	y = 0;
	if (keycode == 4 && mlx->c_button % 2)
		mlx->man_y += 5;
	if (keycode == 5 && mlx->c_button % 2)
		mlx->man_y -= 5;
	if (keycode == 4 && mlx->x_button % 2)
		mlx->ar_y += 5;
	if (keycode == 5 && mlx->x_button % 2)
		mlx->ar_y -= 5;
	return (1);
}
