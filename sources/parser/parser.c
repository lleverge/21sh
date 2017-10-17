/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 15:00:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/04/06 20:03:41 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

static int			final_fork(t_ult *ult, t_exec *exec, char **cmd)
{
	char	**env_cpy;
	char	*path;
	int		status;

	env_cpy = list_in_tab(ult->env);
	path = search_path(ult->path, cmd);
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
		dup2(exec->fd_write, 0);
		close(exec->fd[0]);
		execve(path, cmd, env_cpy);
	}
	else
		waitpid(exec->pid, &status, 0);
	free_tab(env_cpy);
	ft_strdel(&path);
	return (0);
}

int			parser(t_lexer *list, t_ult *ult)
{
	char	**cmd;
	t_exec	*exec;

	while (list)
	{
		exec = create_exec();
		ft_strlen(ult->path[0]);
		cmd = ft_strsplit_ws(list->content);
//		if (list->token_id == PIPE)
//			fork_pipe(ult, exec, cmd);
		if (list->token_id == EOL)
			final_fork(ult, exec, cmd);
		list = list->next;
		free_tab(cmd);
		free_exec(exec);
	}
	return (0);
}
