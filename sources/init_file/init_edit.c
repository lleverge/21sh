/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:57:33 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/15 18:46:36 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

t_edit				*init_edit(t_edit *ed, char **environ)
{
	if (!(ed = (t_edit *)malloc(sizeof(t_edit))))
	{
		ft_putendl_fd("error: edit struct malloc failed", 2);
		exit(-1);
	}
	ed->env = fill_env(environ);
	ed->input = init_input();
	ed->termi = init_term();
	get_ws(ed->termi);
	return (ed);
}
