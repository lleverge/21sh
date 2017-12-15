/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:00:44 by lleverge          #+#    #+#             */
/*   Updated: 2017/11/17 17:20:18 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <builtins.h>

static char			**get_paths(t_env *env)
{
	char			**path_tab;
	char			*path;

	path_tab = NULL;
	path = NULL;
	path = get_node_content(env, "PATH");
	if (path)
	{
		path_tab = ft_strsplit(path, ':');
		ft_strdel(&path);
		return (path_tab);
	}
	ft_strdel(&path);
	return (NULL);
}

t_ult				*stock_ult(t_ult *ult, int i)
{
	static t_ult	*tmp = NULL;

	if (i == 0)
		tmp = ult;
	return (tmp);
}

static t_env				*incr_shlvl(t_env *envlist)
{
	char	*tmp;
	int		shlvl;

	tmp = NULL;
	shlvl = 1;
	if (!(tmp = get_node_content(envlist, "SHLVL")))
	{
		tmp = ft_itoa(shlvl);
		envlist = set_env(envlist, "SHLVL", tmp);
		ft_strdel(&tmp);
		return (envlist);
	}
	shlvl = ft_atoi(tmp);
	shlvl++;
	ft_strdel(&tmp);
	tmp = ft_itoa(shlvl);
	envlist = set_env(envlist, "SHLVL", tmp);
	ft_strdel(&tmp);
	return (envlist);
}

t_ult				*init_ult(t_ult *ult, char **environ)
{
	t_hist			*hist;

	hist = NULL;
	if (!(ult = (t_ult *)malloc(sizeof(t_ult))))
	{
		ft_putendl_fd("error: ult struct malloc failed", 2);
		exit(-1);
	}
	ult->env = fill_env(environ);
	ult->term = init_term();
	ult->path = get_paths(ult->env);
	ult->env = incr_shlvl(ult->env);
	ult->hist = init_hist(hist);
	ult->hash_table = table_init(ult->env);
	ult->cmd = NULL; 
	ult->fd[0] = 0;
	ult->fd[1] = 1;
	ult->fd[2] = 2;
	return (ult);
}
