/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 14:12:34 by vfrolich          #+#    #+#             */
/*   Updated: 2017/12/23 18:09:47 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	check_close(t_process *proc, int i)
{
	int fd;
	t_list *tmp;
	int fd_closed;

	tmp = proc->fd_to_close;
	fd = proc->fd[i];
	fd_closed = -1;
	while (tmp)
	{
		if (fd == *((int *)(tmp->content)))
		{
			close(i);
			fd_closed = i;
		}
		tmp = tmp->next;
	}
	if (i == 0 && i != fd_closed)
		dup2(proc->fd[0], STDIN_FILENO);
	if (i == 1 && i != fd_closed)
		dup2(proc->fd[1], STDOUT_FILENO);
	if (i == 2 && i != fd_closed)
		dup2(proc->fd[2], STDERR_FILENO);
}

int		set_fd_exec(t_process *proc)
{
	int	fd;

	fd = 0;
	while (fd < 3)
	{
		check_close(proc, fd);
		fd++;
	}
	return (0);
}

void	close_fd_exec(t_process *proc)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (proc->fd[i] > 2)
			if (close(proc->fd[i]) == -1)
				ft_putendl_fd("21sh: close error", 2);
		i++;	
	}
}
