/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 17:09:10 by vfrolich          #+#    #+#             */
/*   Updated: 2017/10/21 17:53:04 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

t_process			*append_redirect(t_process *proc)
{
	char			*sub_str;
	char			*file_name;
	int				fd;

	sub_str = ft_strchr(proc->cmd, '>') + 1;
	if (check_error_redir(sub_str) == -1)
	{
		free_process_one(proc);
		return (NULL);
	}
	file_name = get_word(sub_str);
	if ((fd = open(file_name, O_APPEND | O_CREAT | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_putendl_fd("open error", STDERR_FILENO);
		ft_strdel(&file_name);
		free_process_one(proc);
		return (NULL);
	}
	proc->fd[which_fd(proc->cmd)] = fd;
	proc = standard_fd(proc);
	ft_strdel(&file_name);
	return (proc);
}
