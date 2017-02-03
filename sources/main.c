/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/03 16:50:05 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

int			read_entry(char **cmd)
{
	int		i;
	char	**table;

	i = 0;
	if (cmd == NULL)
		return (1);
	while (cmd[i])
	{
		table = ft_strsplit_ws(cmd[i]);
		i++;
		free_tab(table);
	}
	return (0);
}

int			init_all(char **environ)
{
	t_ult	*ult;
	char	*line;

	ult = NULL;
	line = ft_strdup("");
	ult = init_ult(ult, environ);
	while (read_entry(ft_strsplit(line, ';')) != -1)
	{
		prompt(ult->env);
		ft_strdel(&line);
		get_next_line(0, &line);
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
