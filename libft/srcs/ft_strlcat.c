/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:25:44 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/18 23:03:00 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			dst_len;

	dst_len = ft_strlen(dst);
	if (size < dst_len + 1)
		return (size + ft_strlen(src));
	if (size > dst_len + 1)
		ft_strncat(dst, src, size - dst_len - 1);
	return (dst_len + ft_strlen(src));
}
