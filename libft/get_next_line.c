/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:58:21 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/14 17:49:04 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_mem_concat(char *str, char *buffer)
{
	char *tmp;

	tmp = ft_strjoin(str, buffer);
	ft_strdel(&str);
	return (tmp);
}

static int		ft_get_line(char **line, char *buffer, char *overflow)
{
	char *tmp;

	if ((tmp = ft_strchr(buffer, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(buffer);
		ft_memmove(overflow, tmp + 1, ft_strlen(tmp + 1) + 1);
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char overflow[256][BUFF_SIZE + 1];
	char		buffer[BUFF_SIZE + 1];
	char		*str;
	int			ret;

	if (fd < 0 || fd > 256 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (ft_get_line(line, overflow[fd], overflow[fd]) == 1)
		return (1);
	str = ft_strdup(overflow[fd]);
	ft_memset(overflow[fd], 0, BUFF_SIZE + 1);
	ft_bzero(buffer, BUFF_SIZE + 1);
	while ((ret = read(fd, buffer, BUFF_SIZE)) != 0)
	{
		if (ret == -1)
			return (-1);
		buffer[ret] = '\0';
		str = ft_mem_concat(str, buffer);
		if (ft_get_line(line, str, overflow[fd]) == 1)
		{
			ft_strdel(&str);
			return (1);
		}
	}
	return ((*line = str) && ft_strlen(*line) != 0);
}
