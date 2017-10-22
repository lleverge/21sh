/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 17:09:10 by vfrolich          #+#    #+#             */
/*   Updated: 2017/10/22 15:09:53 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

t_process			*append_redirect(t_process *proc)
{
	char			*sub_str;
	char			*file_name;
	int				fd;

	sub_str = ft_strchr(proc->cmd, '>') + 2;
	if (check_error_redir(sub_str, ">>") == -1)
	{
		free_process_one(proc);
		return (NULL);
	}
	file_name = get_word(sub_str);
	if ((fd = open(file_name, O_APPEND | O_CREAT | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		get_open_err(file_name, W_OK);
		ft_strdel(&file_name);
		free_process_one(proc);
		return (NULL);
	}
	proc->fd[which_fd(proc->cmd)] = fd;
	proc = standard_fd(proc);
	ft_strdel(&file_name);
	return (proc);
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

t_process			*redirect_input(t_process *proc)
{
	char			*sub_str;
	char			*file_name;
	int				fd;

	sub_str = ft_strchr(proc->cmd, '<') + 1;
	if (check_error_redir(sub_str, "<") == -1)
	{
		free_process_one(proc);
		return (NULL);
	}
	file_name = get_word(sub_str);
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		get_open_err(file_name, R_OK);
		ft_strdel(&file_name);
		free_process_one(proc);
		return (NULL);
	}
	proc->fd[0] = fd;
	proc = standard_fd(proc);
	ft_strdel(&file_name);
	return (proc);
}
