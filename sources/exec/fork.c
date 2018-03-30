/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:32:12 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/30 14:56:49 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

static void	clean(t_process *proc, char **env_cpy, char **cmd_tab)
{
	close_fd_exec(proc);
	free_tab(env_cpy);
	free_tab(cmd_tab);
}

void		detect_shitty_fd(t_process *proc, int fd[2])
{
	if (fd[0] != proc->fd[0] && fd[0] != proc->fd[1] && fd[0] != proc->fd[2])
		close(fd[0]);
	if (fd[1] != proc->fd[0] && fd[1] != proc->fd[1] && fd[1] != proc->fd[2])
		close(fd[1]);
}

int			exe_fork2(t_env *env, t_process *proc, t_ult *ult, int fd[2])
{
	pid_t	pid;
	char	**env_cpy;
	char	**cmd_tab;
	int		status;

	cmd_tab = ft_strsplit_ws(proc->cmd);
	env_cpy = list_in_tab(env);
	status = 0;
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		reset_term(ult->term);
		detect_shitty_fd(proc, fd);
		if (set_fd_exec(proc) == -1 || execve(*cmd_tab, cmd_tab, env_cpy) < 0)
		{
			ft_putendl_fd("21sh: invalid command", 2);
			exit(-1);
		}
	}
	else
		proc->pid = pid;
	clean(proc, env_cpy, cmd_tab);
	return (status);
}

int			exe_fork(t_env *env, t_process *proc, t_ult *ult, int fd[2])
{
	pid_t	pid;
	char	**env_cpy;
	char	**cmd_tab;
	int		status;

	cmd_tab = ft_strsplit_ws(proc->cmd);
	env_cpy = list_in_tab(env);
	status = 0;
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		reset_term(ult->term);
		detect_shitty_fd(proc, fd);
		if (set_fd_exec(proc) == -1)
			exit(-1);
		execve(hash_search(*cmd_tab, ult->hash_table), cmd_tab, env_cpy);
	}
	else
		proc->pid = pid;
	clean(proc, env_cpy, cmd_tab);
	return (status);
}
