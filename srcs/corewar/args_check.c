/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:06:17 by sdiedra           #+#    #+#             */
/*   Updated: 2019/07/28 16:10:50 by sdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

int		get_arg_size(int arg_type, t_op op)
{
	if (arg_type == T_REG)
		return (1);
	else if (arg_type == 3)
		return (2);
	else if (arg_type == T_DIR)
		return (op.is_short_dir ? 2 : 4);
	else
		return (0);
}

int		arg_check(unsigned char octet, const t_op op)
{
	int				i;
	unsigned char	arg;

	i = 0;
	while (i < op.number)
	{
		arg = get_arg(octet, 2, 7 - i * 2);
		if (arg == 3)
			arg++;
		if (!(arg & op.types_arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int		check_reg1(unsigned int octet)
{
	if (get_arg(octet, 2, 7) == T_REG)
		return (1);
	if (get_arg(octet, 2, 5) == T_REG)
		return (1);
	if (get_arg(octet, 2, 3) == T_REG)
		return (1);
	return (0);
}

int		check_reg(unsigned int octet,
					unsigned char arena[MEM_SIZE], int pos, t_op op)
{
	int	i;
	int	tmp_pos;
	int	arg_type;

	i = 0;
	tmp_pos = (pos + 1) % MEM_SIZE;
	if (!check_reg1(octet))
		return (0);
	while (i < op.number)
	{
		arg_type = get_arg(octet, 2, 7 - i * 2);
		if (arg_type == T_REG)
		{
			if (arena[tmp_pos] < 1 || arena[tmp_pos] > 16)
				return (1);
		}
		tmp_pos = (tmp_pos + get_arg_size(arg_type, op)) % MEM_SIZE;
		i++;
	}
	return (0);
}
