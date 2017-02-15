/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:57:33 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/15 16:54:12 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

t_edit				*init_edit(char **environ)
{
	t_edit		*ed;

	if (!(ed = (t_edit *)malloc(sizeof(t_edit))))
	{
		ft_putendl_fd("error: edit struct malloc failed", 2);
		exit(-1);
	}
	ed->env = fill_env(environ);
	ed->input = init_input();
	if ((ed->fd = open(ttyname(0), O_RDWR)) == -1)
		ft_putendl_fd("error: tyyname", 2);
	get_ws(ed->fd, ed->ws);
	return (ed);
}
