/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:32:12 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/23 18:17:51 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"

int				exe_fork(t_env *env, t_process *proc, t_hashelem **table)
{
	pid_t	pid;
	char	*cmd_path;
	char	**env_cpy;
	char	**cmd_tab;

	cmd_tab = ft_strsplit_ws(proc->cmd);
	cmd_path = hash_search(cmd_tab[0], table);
	env_cpy = list_in_tab(env);
	if ((pid = fork()) == 0)
	{
		if (set_fd_exec(proc) == -1)
			exit(-1);
		if (execve(cmd_path, cmd_tab, env_cpy) < 0)
		{
			ft_putstr_fd("42sh: command not found: ", 2);
			ft_putendl_fd(cmd_tab[0], 2);
			exit(127);
		}
	}
	wait(0);
	close_fd_exec(proc);
	free_tab(env_cpy);
	free_tab(cmd_tab);
	return (0);
}
