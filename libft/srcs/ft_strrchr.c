/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 22:30:03 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/11 22:48:37 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrchr(const char *s, int c)
{
	size_t			s_len;

	s_len = ft_strlen((char *)s);
	while (s_len + 1)
		if (*(s + s_len--) == (char)c)
			return ((char *)(s + s_len + 1));
	return (NULL);
}
