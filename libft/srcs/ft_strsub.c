/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 01:28:23 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/12 01:32:55 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*a;
	char			*str;

	if (!s || !(a = (char *)malloc(len + 1)))
		return (NULL);
	str = a;
	while (len--)
		*(a++) = *(s + start++);
	*a = '\0';
	return (str);
}
