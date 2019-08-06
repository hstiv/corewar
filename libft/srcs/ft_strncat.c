/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:08:45 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/12 02:13:19 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strncat(char *s1, const char *s2, size_t n)
{
	char			*d;

	d = s1 + ft_strlen(s1);
	while (*s2 && n--)
		*(d++) = *(s2++);
	*d = '\0';
	return (s1);
}