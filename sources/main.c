/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/16 17:52:42 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

int				init_all(char **environ)
{
	t_ult		*ult;
	t_edit		*ed;
	t_key		*key;

	ult = NULL;
	ed = NULL;
	key = NULL;
	ult = init_ult(ult, environ);
	ed = init_edit(ed, environ);
	init_tkey(ed, &key);
	while (42)
	{
		prompt(ed);
		line_edition(key, ed);
		ft_putchar('\n');
	}
	return (0);
}

int				main(int ac, char **av, char **environ)
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
