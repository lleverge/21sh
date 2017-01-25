/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/25 17:28:05 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			read_entry(char **cmd)
{
	int		i;
	char	**tab;

	i = 0;
	if (cmd == NULL)
		return (1);
	while (cmd[i])
	{
		tab = ft_strsplit_ws(cmd[i]);
		i++;
		free_tab(tab);
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
		ft_putendl_fd("error: 21sh requires no arguments", 2);
	init_all(environ);
	return (0);
}
