/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:32:12 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/26 16:18:51 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

int				exe_fork2(t_env *env, t_process *proc, char *cmd_path)
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
		if (set_fd_exec(proc) == -1)
			exit(-1);
		if (execve(cmd_path ,cmd_tab, env_cpy) < 0)
		{
			ft_putstr_fd("21sh: execve error", 2);
			exit(127);
		}
	}
	wait(&status);
	close_fd_exec(proc);
	free_tab(env_cpy);
	free_tab(cmd_tab);
	return (status);
}

int				exe_fork(t_env *env, t_process *proc, t_ult *ult)
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
		if (set_fd_exec(proc) == -1)
			exit(-1);
		if (execve(hash_search(*cmd_tab, ult->hash_table),
			cmd_tab, env_cpy) < 0)
		{
			ft_putstr_fd("21sh: execve error", 2);
			exit(127);
		}
	}
	wait(&status);
	close_fd_exec(proc);
	free_tab(env_cpy);
	free_tab(cmd_tab);
	return (status);
}
