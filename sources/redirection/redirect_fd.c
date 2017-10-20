/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 14:13:00 by vfrolich          #+#    #+#             */
/*   Updated: 2017/10/20 20:19:05 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

static char	*get_word(char *sub_cmd)
{
	size_t	w_length;
	size_t	w_start;
	char	*tmp;

	w_length = 0;
	w_start = 0;
	tmp = sub_cmd;
	while (tmp[w_start] && (tmp[w_start] < 33 || tmp[w_start] > 126))
		w_start++;
	tmp = &tmp[w_start];
	while (tmp[w_length] && (tmp[w_length] >= 33 && tmp[w_length] <= 126))
		w_length++;
	return (ft_strsub(sub_cmd, w_start, w_length));
}

static int	check_error(char *sub_cmd)
{
	if (!sub_cmd || !*sub_cmd)
	{
		ft_putendl_fd("parse error near '>'", STDERR_FILENO);
		return (-1);
	}
	while (*sub_cmd && (*sub_cmd < 33 || *sub_cmd > 126))
		sub_cmd++;
	if (!*sub_cmd)
	{
		ft_putendl_fd("parse error near '>'", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

t_process	*simple_redirect(t_process *proc)
{
	char	*sub_str;
	char	*file_name;
	int		fd;

	sub_str = ft_strchr(proc->cmd, '>') + 1;
	if (check_error(sub_str) == -1)
		return (NULL);
	file_name = get_word(sub_str);
	if ((fd = open(file_name, O_TRUNC | O_CREAT | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_putendl_fd("open error", STDERR_FILENO);
		ft_strdel(&file_name);
		return (NULL);
	}
	proc->fd[1] = fd;
	ft_strdel(&file_name);
	return (proc);
}
