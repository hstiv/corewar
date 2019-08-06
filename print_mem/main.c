/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 04:17:47 by ubyrd             #+#    #+#             */
/*   Updated: 2019/07/17 06:48:20 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFF_SIZE	16

void			exit_mes(char *mes)
{
	mes ? printf("%s", mes) : 0;
	exit(1);
}

void			print_byte(unsigned char byte, int i, int bytes)
{
	i > 0 && !(i % 2) && i < bytes ? printf(" ") : 0;
	printf("%c", byte / 16 > 9 ? 'a' + byte / 16 - 10 : '0' + byte / 16);
	printf("%c", byte % 16 > 9 ? 'a' + byte % 16 - 10 : '0' + byte % 16);
}

int				main(int argc, char **argv)
{
	int				fd;
	unsigned char	buff[BUFF_SIZE];
	int				bytes;
	int				flag;
	int				i;

	argc != 2 ? exit_mes("Usage: ./hex_read filename\n") : 0;
	(fd = open(argv[1], O_RDONLY)) == -1 ? exit_mes("Can't open file\n") : 0;
	flag = 1;
	while (1)
	{
		if ((bytes = read(fd, buff, BUFF_SIZE)) == -1)
			exit_mes("Can't read file\n");
		bytes ? flag = 0 : 0;
		i = -1;
		while (++i < bytes)
			print_byte(buff[i], i, bytes);
		bytes ? printf("\n") : 0;
		if (bytes < BUFF_SIZE)
			break ;
	}
	flag ? printf("\n") : 0;
	return (0);
}
