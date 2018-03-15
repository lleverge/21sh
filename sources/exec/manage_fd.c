/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 14:12:34 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/15 19:05:09 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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

void	check_close(t_process *proc, int i)
{
	int		fd;
	t_close	*tmp;
	int		fd_closed;

	tmp = proc->fd_to_close;
	fd = proc->fd[i];
	fd_closed = -1;
	while (tmp)
	{
		if (fd == tmp->fd)
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
	// ft_putendl("for this process :");
	// ft_putstr("stdin is ");
	// ft_putnbrendl(proc->fd[0]);
	// ft_putstr("stduut is ");
	// ft_putnbrendl(proc->fd[1]);
	// ft_putstr("stderr is ");
	// ft_putnbrendl(proc->fd[2]);
	while (i < 3)
	{
		if (proc->fd[i] > 2)
		{
			// ft_putstr("we close :");
			// ft_putnbrendl(proc->fd[i]);
			if (close(proc->fd[i]) == -1)
				ft_putendl_fd("21sh: close error", 2);
		}
		i++;	
	}
}
