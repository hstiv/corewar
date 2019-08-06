/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 23:00:14 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/12 02:14:10 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *haystack,
							const char *needle, size_t len)
{
	size_t			i;
	size_t			j;

	if (!*needle)
		return ((char *)haystack);
	i = -1;
	while (*(haystack + ++i))
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j))
			if (!*(needle + ++j) || (i + j) > len)
				return ((i + j) > len ? NULL : (char *)(haystack + i));
	}
	return (NULL);
}
