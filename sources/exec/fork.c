/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:32:12 by lleverge          #+#    #+#             */
/*   Updated: 2018/01/14 17:55:05 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>
#include <stdio.h>

static void	clean(t_process *proc, t_ult *ult, char **env_cpy, char **cmd_tab)
{
	close_fd_exec(proc);
	free(ult->term);
	ult->term = init_term();
	free_tab(env_cpy);
	free_tab(cmd_tab);
}

int			exe_fork2(t_env *env, t_process *proc, char *cmd_path, t_ult * ult)
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
		if (set_fd_exec(proc) == -1 || execve(cmd_path ,cmd_tab, env_cpy) < 0)
			exit(-1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
	}
	clean(proc, ult, env_cpy, cmd_tab);
	return (status);
}

int			exe_fork(t_env *env, t_process *proc, t_ult *ult)
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
		if (set_fd_exec(proc) == -1)
			exit(-1);
		execve(hash_search(*cmd_tab, ult->hash_table), cmd_tab, env_cpy);
	}
	else 
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
	}
	clean(proc, ult, env_cpy, cmd_tab);
	return (status);
}
