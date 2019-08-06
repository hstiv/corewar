/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 12:30:19 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/29 23:42:21 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_buf	*lstreturn(t_list **root, const int fd, char **line)
{
	t_list			*temp_lst;
	t_buf			temp_buf;

	if (fd < 0 || !line || !(*line = ft_strnew(0)))
		return (NULL);
	if (!*root)
	{
		temp_buf.fd = fd;
		ft_bzero((char *)temp_buf.buf, BUFF_SIZE + 1);
		*root = ft_lstnew(&temp_buf, sizeof(t_buf));
		return (*root ? (t_buf *)(*root)->content : NULL);
	}
	temp_lst = *root;
	while (temp_lst)
	{
		if (((t_buf *)temp_lst->content)->fd == fd)
			return ((t_buf *)temp_lst->content);
		if (temp_lst->next == NULL)
			break ;
		temp_lst = temp_lst->next;
	}
	temp_buf.fd = fd;
	ft_bzero((char *)temp_buf.buf, BUFF_SIZE + 1);
	temp_lst->next = ft_lstnew(&temp_buf, sizeof(t_buf));
	return (temp_lst->next ? (t_buf *)temp_lst->next->content : NULL);
}

static int		linefunc(const int func_param, char **s1, char *s2, int i)
{
	char			*temp;

	if (func_param == LINE_EOL)
	{
		while (s2[i] && s2[i] != '\n')
			i++;
		if (s2[i] == '\n')
		{
			s2[i] = '\0';
			return (i);
		}
	}
	else if (func_param >= LINE_ADD && func_param <= LINE_ZERO)
	{
		if (!(temp = ft_strjoin(*s1, s2)))
			return (GNL_ERR);
		free((void *)*s1);
		*s1 = temp;
		if (func_param == LINE_CPY)
			ft_strcpy(s2, s2 + i + 1);
		else if (func_param == LINE_ZERO)
			ft_bzero((char *)s2, BUFF_SIZE + 1);
		return (GNL_OK);
	}
	return (func_param == LINE_EOL ? NO_EOL : GNL_ERR);
}

static t_list	**lstroot(const int func_param)
{
	static t_list	*root;
	t_list			*temp;

	if (func_param == GET_ROOT)
		return (&root);
	else if (func_param == FREE_ROOT)
		while (root)
		{
			free(root->content);
			temp = root->next;
			free((void *)root);
			root = temp;
		}
	return (NULL);
}

int				gnl_buffree(const int func_param, const int fd)
{
	t_list			**root;
	t_list			*temp1;
	t_list			*temp2;

	if ((root = lstroot(GET_ROOT)) && func_param == FREE_ALL)
		return (!lstroot(FREE_ROOT) ? GNL_END : GNL_END);
	if (fd < 0 || !*root || func_param != FREE_ELEM)
		return (GNL_ERR);
	if (((t_buf *)(*root)->content)->fd == fd)
	{
		temp1 = (*root)->next;
		free((*root)->content);
		free((void *)*root);
		*root = temp1;
		return (GNL_END);
	}
	temp1 = (*root);
	while (temp1->next && ((t_buf *)temp1->next->content)->fd != fd)
		temp1 = temp1->next;
	if (!(temp1->next))
		return (GNL_ERR);
	temp2 = temp1->next->next;
	free(temp1->next->content);
	free((void *)temp1->next);
	return ((temp1->next = temp2) ? GNL_END : GNL_END);
}

int				get_next_line(const int fd, char **line)
{
	t_buf			*buf;
	int				i;
	int				ind;

	if (!(buf = lstreturn(lstroot(GET_ROOT), fd, line)))
		return (GNL_ERR);
	if ((i = linefunc(LINE_EOL, NO_PARAM, buf->buf, NO_PARAM)) != NO_EOL)
		return (linefunc(LINE_CPY, line, buf->buf, i));
	if (linefunc(LINE_ZERO, line, buf->buf, NO_PARAM) == GNL_ERR)
		return (GNL_ERR);
	while ((ind = read(fd, buf->buf, BUFF_SIZE)) != READ_ERR)
	{
		*(buf->buf + ind) = '\0';
		if ((i = linefunc(LINE_EOL, NO_PARAM, buf->buf, NO_PARAM)) != NO_EOL)
			return (linefunc(LINE_CPY, line, buf->buf, i));
		if (ind < BUFF_SIZE && *(buf->buf))
			return (linefunc(LINE_ZERO, line, buf->buf, NO_PARAM));
		if (linefunc(LINE_ADD, line, buf->buf, NO_PARAM) == GNL_ERR)
			return (GNL_ERR);
		if (ind < BUFF_SIZE && **line)
			return (GNL_OK);
		if (!ind)
			return (gnl_buffree(FREE_ELEM, fd));
	}
	return (GNL_ERR);
}
