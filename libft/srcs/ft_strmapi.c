/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 01:15:14 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/12 01:18:03 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*a;
	unsigned int	i;

	if (!s || !f || !(a = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	i = -1;
	while (s[++i])
		a[i] = (*f)(i, s[i]);
	a[i] = '\0';
	return (a);
}
