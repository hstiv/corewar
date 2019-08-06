/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 01:07:54 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/12 01:17:55 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strmap(char const *s, char (*f)(char))
{
	char			*a;
	char			*str;

	if (!s || !f || !(a = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	str = a;
	while (*s)
		*(a++) = (*f)(*(s++));
	*a = '\0';
	return (str);
}
