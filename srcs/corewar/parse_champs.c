/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiedra <sdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:56:39 by sdiedra           #+#    #+#             */
/*   Updated: 2019/07/30 16:08:44 by sdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corvm.h"

void	champ_error(int i, char *s)
{
	if (!i)
		ft_printf("Can't read source file %s\n", s);
	else if (i == 1)
		ft_printf("Error: File %s has too large a code\n", s);
	else if (i == 2)
		ft_printf("Error: Wrong name format file %s\n", s);
	else
		ft_printf("ERROR\n", s);
	exit(0);
}

int		read_4bytes(int fd)
{
	int				ret;
	unsigned char	octs[4];
	int				total;

	ret = read(fd, octs, sizeof(unsigned char) * 4);
	if (ret >= 0 && ret != 4)
		return (0);
	else if (ret < 0)
		champ_error(3, NULL);
	total = (octs[0] << 24) | (octs[1] << 16) | (octs[2] << 8) | octs[3];
	return (total);
}

int		check_null(int fd)
{
	int				i;
	unsigned char	octs[4];
	int				number;

	i = read(fd, octs, sizeof(unsigned char) * 4);
	if (i >= 0 && i != 4)
		number = 0;
	else if (i < 0)
		champ_error(3, NULL);
	number = (octs[0] << 24) | (octs[1] << 16) | (octs[2] << 8) | octs[3];
	if (number == 0)
		return (1);
	else
		return (0);
}

void	parse_champs(t_vm *vm, char *name, int n, int number)
{
	int	fd;
	int	i;

	if ((fd = open(name, O_RDONLY)) < 0)
		champ_error(0, name);
	if ((i = read_4bytes(fd)) != COREWAR_EXEC_MAGIC)
		champ_error(0, name);
	if ((i = read(fd, &(vm->champs[n].name), PROG_NAME_LENGTH)) <= 0)
		champ_error(2, name);
	if (!check_null(fd))
		champ_error(2, name);
	if ((vm->champs[n].exec_code = read_4bytes(fd)) > CHAMP_MAX_SIZE)
		champ_error(1, name);
	if ((i = read(fd, &(vm->champs[n].comment), COMMENT_LENGTH)) <= 0)
		champ_error(2, name);
	if (!check_null(fd))
		champ_error(2, name);
	if ((i = read(fd, &(vm->champs[n].champ_bin), CHAMP_MAX_SIZE)) <= 0)
		champ_error(2, name);
	if (i != vm->champs[n].exec_code)
		champ_error(2, name);
	vm->champs[n].n_place = number;
	vm->champs[n].live = 0;
	vm->champs[n].lives_in_period = 0;
	close(fd);
}
