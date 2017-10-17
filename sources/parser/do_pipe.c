/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:14:10 by lleverge          #+#    #+#             */
/*   Updated: 2017/04/06 19:24:40 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

int		fork_pipe(t_ult *ult, t_exec *exec, char **cmd1)
{
	char	**env_cpy;
	char	*path;
	
	
	env_cpy = list_in_tab(ult->env);
	path = search_path(ult->path, cmd1);
	if (pipe(exec->fd) == -1)
	{
		ft_putendl_fd("pipe", 2);
		exit(-1);
	}
	if ((exec->pid = fork()) == -1)
	{
		ft_putendl_fd("fork", 2);
		exit(-1);
	}
	if (exec->pid == 0)
	{
		close(exec->fd[1]);
		dup2(exec->fd[0], 0);
		close(exec->fd[0]);
		execve(path, cmd1, env_cpy);
	}
	else
	{
		wait(NULL);
		close(exec->fd[1]);
		exec->fd_write = exec->fd[0];
	}
	ft_strdel(&path);
	free_tab(env_cpy);
	return (0);
}
