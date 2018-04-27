/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:11:01 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/27 18:13:30 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

char				*get_word(char *sub_cmd)
{
	size_t			w_length;
	size_t			w_start;
	char			*tmp;

	w_length = 0;
	w_start = 0;
	tmp = sub_cmd;
	while (tmp[w_start] && (tmp[w_start] < 33 || tmp[w_start] > 126))
		w_start++;
	tmp = &tmp[w_start];
	if (tmp && (*tmp == '\'' || *tmp == '\"'))
		w_length = get_wordlen(tmp);
	else
	{
		while (tmp[w_length] && (tmp[w_length] >= 33 && tmp[w_length] <= 126))
			w_length++;
	}
	if (*tmp && (*tmp == '\'' || *tmp == '\"'))
		w_start++;
	return (ft_strsub(sub_cmd, w_start, w_length));
}

int					check_error_redir(char *sub_cmd, char *error_char)
{
	if (!sub_cmd || !*sub_cmd)
	{
		ft_putstr_fd("parse error near '", STDERR_FILENO);
		ft_putstr_fd(error_char, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		return (-1);
	}
	while (*sub_cmd && (*sub_cmd < 33 || *sub_cmd > 126))
		sub_cmd++;
	if (!*sub_cmd)
	{
		ft_putstr_fd("parse error near '", STDERR_FILENO);
		ft_putstr_fd(error_char, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

t_process			*standard_fd(t_process *proc)
{
	if (!proc)
		return (NULL);
	if (proc->fd[0] == -1)
		proc->fd[0] = 0;
	if (proc->fd[1] == -1)
		proc->fd[1] = 1;
	if (proc->fd[2] == -1)
		proc->fd[2] = 2;
	return (proc);
}

int					which_fd(char *cmd)
{
	char			*sub_cmd;
	int				i;
	int				fd;

	sub_cmd = cmd;
	sub_cmd = ft_strsub(sub_cmd, 0, (ft_strchr(sub_cmd, '>') - sub_cmd));
	if (!ft_strlen(sub_cmd))
	{
		sub_cmd ? ft_strdel(&sub_cmd) : NULL;
		return (1);
	}
	i = ft_strlen(sub_cmd) - 1;
	if (ft_isdigit(sub_cmd[i]))
	{
		while (i > 0 && ft_isdigit(sub_cmd[i]))
			i--;
	}
	fd = ft_atoi(&sub_cmd[i]);
	ft_strdel(&sub_cmd);
	return (fd);
}

void				get_open_err(char *file_name, int access_mode)
{
	if (access(file_name, F_OK) == -1)
	{
		ft_putstr_fd("21sh: no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(file_name, STDERR_FILENO);
		return ;
	}
	if (access(file_name, access_mode) == -1)
	{
		ft_putstr_fd("21sh: permission denied: ", STDERR_FILENO);
		ft_putendl_fd(file_name, STDERR_FILENO);
	}
}
