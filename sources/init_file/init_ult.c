/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:00:44 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/07 09:07:26 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static char		**get_paths(t_env *env)
{
	char	**path_tab;
	char	*path;

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

t_ult			*init_ult(t_ult *ult, char **environ)
{
	t_hist		*hist;

	hist = NULL;
	if (!(ult = (t_ult *)malloc(sizeof(t_ult))))
	{
		ft_putendl_fd("error: ult struct malloc failed", 2);
		exit(-1);
	}
	ult->env = fill_env(environ);
	ult->term = init_term();
	ult->path = get_paths(ult->env);
	ult->hist = init_hist(hist);
	return (ult);
}
