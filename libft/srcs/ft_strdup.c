/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 23:34:53 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/10 23:54:27 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strdup(const char *s1)
{
	char			*dest;

	if (!(dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	return (ft_strcpy(dest, s1));
}
