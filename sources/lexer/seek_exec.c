/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:47:13 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/12 16:07:24 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static int		builtin_launch(t_ult *ult, t_process *proc)
{
	int		fd[3];
	int		ret;

	fd[0] = dup(ult->fd[0]);
	fd[1] = dup(ult->fd[1]);
	fd[2] = dup(ult->fd[2]);
	set_fd_exec(proc);
	ret = search_for_builtins(ult, proc);
	close_fd_exec(proc);
	restore_fd(fd);
	return (ret);
}

int				seek_and_exec(t_ult *ult, t_process *proc,
							char **cmd_tab, int fd[2])
{
	char	**cmd_tab2;

	cmd_tab2 = cmd_tab;
	if (!cmd_tab)
	{
		ft_putendl_fd("21sh : command not found", 2);
		return (127);
	}
	if (check_for_builtin(*cmd_tab))
		return (builtin_launch(ult, proc));
	if (ult->hash_table && hash_search(*cmd_tab, ult->hash_table))
		return (exe_fork(ult->env, proc, ult, fd));
	if (ft_strchr(*cmd_tab, '/') && !path_access_checker(*cmd_tab))
		return (exe_fork2(ult->env, proc, ult, fd));
	if (!ft_strchr(*cmd_tab, '/'))
	{
		ft_putstr_fd("21sh : command not found: ", 2);
		ft_putendl_fd(*cmd_tab, 2);
	}
	return (127);
}
