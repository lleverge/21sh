/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/15 18:42:58 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

int			init_all(char **environ)
{
	t_ult		*ult;
	t_edit		*ed;
	char		*line;

	ult = NULL;
	ed = NULL;
	line = ft_strdup("");
	ult = init_ult(ult, environ);
	ed = init_edit(ed, environ);
	while (42)
	{
		prompt(ed);
		ft_strdel(&line);
		ft_keyspot(ed);
		ft_putchar('\n');
	}
	ft_strdel(&line);
	return (0);
}

int			main(int ac, char **av, char **environ)
{
	av = NULL;
	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("error: 21sh requires no arguments", 2);
		exit(-1);
	}
	init_all(environ);
	return (0);
}
