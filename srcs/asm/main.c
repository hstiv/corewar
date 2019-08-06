/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 05:00:06 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/30 12:04:32 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				main(int argc, char **argv)
{
	t_asm			a;

	ft_bzero(&a, sizeof(a));
	if (argc != 2)
		fail(&a, S_USAGE);
	a.source_file = argv[1];
	if ((a.fd = open(a.source_file, O_RDONLY)) == -1)
		fail(&a, S_ERR_OPEN, a.source_file);
	if (ft_strcmp(SOURCE_EXT, ft_strrchr(a.source_file, '.')))
		fail(&a, S_ERR_EXT, a.source_file);
	handling_header(&a);
	handling_op(&a);
	file_output(&a, a.source_file);
	success(&a, S_NULL_STRING);
}
