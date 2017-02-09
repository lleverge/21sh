/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/09 15:05:42 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

int			init_all(char **environ)
{
	t_ult	*ult;
	char	*line;

	ult = NULL;
	line = ft_strdup("");
	ult = init_ult(ult, environ);
	while (42)
	{
		prompt(ult->env);
		ft_strdel(&line);
		ft_keyspot();
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
