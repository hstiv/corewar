/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:16:40 by sdiedra           #+#    #+#             */
/*   Updated: 2019/07/31 18:02:26 by sdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

void			threw(char *s)
{
	(s != NULL) ? write(1, s, ft_strlen(s)) : 0;
	exit(0);
}

int				rev_byte(t_vm *vm, unsigned int pc, int nbytes)
{
	unsigned char two_bytes[2];
	unsigned char four_bytes[4];

	if (nbytes == 2)
	{
		two_bytes[0] = vm->arena[(pc + 1) % MEM_SIZE];
		two_bytes[1] = vm->arena[pc % MEM_SIZE];
		return (*(short *)&two_bytes[0]);
	}
	if (nbytes == 4)
	{
		four_bytes[0] = vm->arena[(pc + 3) % MEM_SIZE];
		four_bytes[1] = vm->arena[(pc + 2) % MEM_SIZE];
		four_bytes[2] = vm->arena[(pc + 1) % MEM_SIZE];
		four_bytes[3] = vm->arena[pc % MEM_SIZE];
		return (*(int *)&four_bytes[0]);
	}
	return (-1);
}

void			show_dump(t_vm *vm)
{
	int	i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0 && i)
			ft_printf("%#.4x : ", i);
		ft_printf("%02hhx ", vm->arena[i]);
		if ((i + 1) % 32 == 0 && i)
			ft_printf("\n");
		i++;
	}
	exit(0);
}

int				ft_isdigit_s(char *s)
{
	int				i;

	i = (s[0] == '-') ? 1 : 0;
	while (s[i])
	{
		if (!(s[i] >= 48 && s[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

int				get_arg(int octet, int k, int p)
{
	return (((1 << k) - 1) & (octet >> (p - 1)));
}
