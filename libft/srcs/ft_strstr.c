/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 22:49:53 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/12 01:48:30 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strstr(const char *haystack, const char *needle)
{
	size_t			i;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		i = 0;
		while (*(haystack + i) == *(needle + i))
			if (!*(needle + ++i))
				return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
