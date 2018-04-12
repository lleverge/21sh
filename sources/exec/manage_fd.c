/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 14:12:34 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 16:05:53 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	restore_fd(int fd[3])
{
	if (dup2(fd[0], 0) == -1)
		ft_putendl_fd("21sh: error while restoring standard input", 2);
	if (dup2(fd[1], 1) == -1)
		ft_putendl_fd("21sh: error while restoring standard output", 2);
	if (dup2(fd[2], 2) == -1)
		ft_putendl_fd("21sh: error while restoring standard error output", 2);
	if (close(fd[0]) == -1)
		ft_putendl_fd("21sh: error while closing saved standard intput", 2);
	if (close(fd[1]) == -1)
		ft_putendl_fd("21sh: error while closing saved standard output", 2);
	if (close(fd[2]) == -1)
		ft_putendl_fd("21sh: error while closing saved err output", 2);
}

static void	close_fd(t_close *fd_list)
{
	t_close *tmp;

	tmp = fd_list;
	while (tmp)
	{
		close(tmp->fd);
		tmp = tmp->next;
	}
}

void		set_fd_exec(t_process *proc)
{
	close_fd(proc->fd_to_close);
	if (dup2(proc->fd[0], STDIN_FILENO) == -1)
		close(STDIN_FILENO);
	if (dup2(proc->fd[1], STDOUT_FILENO) == -1)
		close(STDOUT_FILENO);
	if (dup2(proc->fd[2], STDERR_FILENO) == -1)
		close(STDERR_FILENO);

}

void	close_fd_exec(t_process *proc)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (proc->fd[i] > 2)
			close(proc->fd[i]);
		i++;
	}
}
