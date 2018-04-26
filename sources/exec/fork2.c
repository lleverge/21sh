/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:59:00 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/26 15:50:18 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static void		detect_fd(t_process *proc, int fd[2])
{
	if (fd[0] != proc->fd[0] && fd[0] != proc->fd[1] && fd[0] != proc->fd[2])
		close(fd[0]);
	if (fd[1] != proc->fd[0] && fd[1] != proc->fd[1] && fd[1] != proc->fd[2])
		close(fd[1]);
}

static int		no_launch(char **cmd_tab, t_ult *ult)
{
	if (!cmd_tab)
		return (1);
	if (check_for_builtin(*cmd_tab))
		return (0);
	if (ult->hash_table && hash_search(*cmd_tab, ult->hash_table))
		return (0);
	if (ft_strchr(*cmd_tab, '/') && !path_access_checker(*cmd_tab))
		return (0);
	if (!ft_strchr(*cmd_tab, '/'))
	{
		ft_putstr_fd("21sh : command not found: ", 2);
		ft_putendl_fd(*cmd_tab, 2);
		return (1);
	}
	return (1);
}

static void		simple_fork(t_ult *ult, char **cmd_tab, t_process *proc,
							char **env_cpy)
{
	if (check_for_builtin(*cmd_tab))
		exit(search_for_builtins(ult, proc));
	else if (ult->hash_table && hash_search(*cmd_tab, ult->hash_table))
		execve(hash_search(*cmd_tab, ult->hash_table), cmd_tab, env_cpy);
	else if (ft_strchr(*cmd_tab, '/') && !path_access_checker(*cmd_tab))
		execve(*cmd_tab, cmd_tab, env_cpy);
}

void			fork_setup(t_process *proc, t_ult *ult, int fd[2])
{
	pid_t	pid;
	char	**cmd_tab;
	char	**env_cpy;

	cmd_tab = cmd_format(proc->cmd);
	if (no_launch(cmd_tab, ult))
	{
		proc->done = 127;
		cmd_tab ? free_tab(cmd_tab) : NULL;
		return ;
	}
	env_cpy = list_in_tab(ult->env);
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		reset_term(ult->term);
		detect_fd(proc, fd);
		set_fd_exec(proc);
		simple_fork(ult, cmd_tab, proc, env_cpy);
	}
	else
		proc->pid = pid;
	exe_clean(proc, env_cpy, cmd_tab);
}
