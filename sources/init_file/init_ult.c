/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:00:44 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/09 18:56:37 by lleverge         ###   ########.fr       */
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
	if (!(ult = (t_ult *)malloc(sizeof(t_ult))))
	{
		ft_putendl_fd("error: ult struct malloc failed", 2);
		return (NULL);
	}
	ult->env = fill_env(environ);
	ult->term = init_term();
	ult->prom = init_prompt();
	ult->curs = init_cursor();
	ult->path = get_paths(ult->env);
	get_ws(ult);
	return (ult);
}
