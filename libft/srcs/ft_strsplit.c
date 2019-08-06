/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 02:15:18 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/18 16:47:31 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		word_counter(char const *s, char c)
{
	int				word_count;

	word_count = 0;
	while (*s)
		if (*s == c)
			s++;
		else
		{
			word_count++;
			while (*s && *s != c)
				s++;
		}
	return (word_count);
}

static char		**tab_free(char **a, size_t k)
{
	while (k)
		free((void *)a[--k]);
	free((void *)a);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char			**a;
	size_t			i;
	size_t			k;

	if (!s || !c)
		return (NULL);
	if (!(a = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1))))
		return (NULL);
	k = 0;
	while (*s)
		if (*s == c)
			s++;
		else
		{
			i = 0;
			while (s[i] && s[i] != c)
				i++;
			if (!(a[k] = ft_strsub(s, 0, i)))
				return (tab_free(a, k));
			s = s + i;
			k++;
		}
	a[k] = NULL;
	return (a);
}
