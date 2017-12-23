/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 14:12:34 by vfrolich          #+#    #+#             */
/*   Updated: 2017/12/23 16:42:26 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		set_fd_exec(t_process *proc)
{
	int	fd;

	fd = 0;
	if (dup2(proc->fd[0], STDIN_FILENO) == -1)
	{
		ft_putendl_fd("21sh: dup2 err", 2);
		return (-1);
	}
	if (dup2(proc->fd[1], STDOUT_FILENO) == -1)
	{
		ft_putendl_fd("21sh: dup2 err", 2);
		return (-1);
	}
	if (dup2(proc->fd[2], STDERR_FILENO) == -1)
	{
		ft_putendl_fd("21sh: dup2 err", 2);
		return (-1);
	}
	return (0);
}
