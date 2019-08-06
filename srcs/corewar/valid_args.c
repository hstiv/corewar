/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:46:28 by sdiedra           #+#    #+#             */
/*   Updated: 2019/07/28 20:17:02 by sdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

int					ischamp(char *s)
{
	char	*c;

	if ((c = ft_strstr(s, ".cor")) == NULL)
		return (0);
	if (ft_strlen(c) > 4 || ft_strlen(s) <= 4)
		return (0);
	return (1);
}

void				is_dump_flag(t_vm *vm, char **av, int c, int *i)
{
	(vm->dump_cycles >= 0) ?
		threw("Error: [[-dump] arg] must be declared once.\n") : 0;
	if (!ft_strcmp("-dump", av[*i]))
	{
		if (*i + 1 < c && ft_isdigit_s(av[*i + 1]))
			vm->dump_cycles = ft_atoi(av[++(*i)]);
		else
			threw(USAGE);
	}
}

int					is_nflag(char **s, int *i, int c)
{
	int	n;

	n = 0;
	if (!ft_strcmp("-n", s[*i]))
	{
		if (*i + 1 < c && ft_isdigit_s(s[*i + 1]))
		{
			(*i)++;
			n = ft_atoi(s[*i]);
			if (n <= 0 || n > MAX_PLAYERS)
				threw("Error: Wrong [[-n] value]\n");
		}
		else
			threw("Error: Wrong [[-n] value]\n");
		if (*i + 1 < c && ischamp(s[*i + 1]))
			(*i)++;
		else
			threw(USAGE);
	}
	return (n);
}

void				eat_vizu(t_vm *vm)
{
	if (vm->champ_nb != 0)
		threw("Error: [-vi] must be declared before champs.\n");
	if (vm->mlx)
		threw("Error: [-vi] must be declared once.\n");
	init_mlx_args(vm);
	(vm->mlx) ? vm->mlx->memsize = MEM_SIZE :
			threw("Error: something wrong in [eat_vizu] func");
}
