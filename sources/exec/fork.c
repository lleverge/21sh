/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:32:12 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/23 16:55:09 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"

char			**path_in_tab(t_env *env, char **cmd)
{
	char	**path_tab;
	int		nb_dir;
	char	*bin_path;

	nb_dir = 0;
	path_tab = NULL;
	bin_path = ft_getbin_path(cmd[0]);
	while (env)
	{
		if (ft_strcmp(env->name, "PATH") == 0 && bin_path == NULL)
			path_tab = ft_strsplit(env->content, ':');
		env = env->next;
	}
	if (!path_tab)
	{
		if ((path_tab = (char **)malloc(sizeof(char *) * 2)))
		{
			path_tab[0] = ft_getbin_path(cmd[0]);
			path_tab[1] = NULL;
		}
		else
			return (NULL);
	}
	ft_strdel(&bin_path);
	return (path_tab);
}

char			*search_path(char **path_tab, char **cmd)
{
	char			*tmp;
	char			*tmp2;
	int				i;

	i = -1;
	tmp = NULL;
	tmp2 = ft_getbin_name(cmd[0]);
	if (!path_tab || !cmd)
		return (NULL);
	return (search_path2(tmp2, tmp, path_tab, i));
}

int				exe_fork2(char **cmd, char **path_tab)
{
	pid_t	pid;
	char	*cmd_path;

	if ((cmd_path = search_path(path_tab, cmd)) == NULL)
	{
		ft_env_error(cmd[0]);
		free_tab(path_tab);
		return (-1);
	}
	pid = fork();
	if (pid > 0)
		wait(0);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (cmd[0][ft_strlen(cmd[0])] != '/')
			cmd_path = ft_strjoin(cmd_path, "/");
		cmd_path = ft_strjoin(cmd_path, ft_getbin_name(cmd[0]));
		if (env_manage_error(cmd_path) != -1)
			execve(cmd_path, cmd, NULL);
	}
	ft_strdel(&cmd_path);
	free_tab(path_tab);
	return (0);
}

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
