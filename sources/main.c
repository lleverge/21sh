/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/19 18:00:02 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>
#include <cmd_edit.h>

int				init_all(char **environ)
{
	t_ult		*ult;
	t_process	*proc;
	char		**cmd;
	int			i;

	ult = NULL;
	proc = NULL;
	ult = init_ult(ult, environ);
	while (42)
	{
		i = 0;
		get_prompt(ult->env);
		termcap(ult);
		ft_putchar('\n');
		cmd = ft_strsplit(ult->cmd, ';');
		while (cmd[i])
		{
			new_lexer(cmd[i]);
			i++;
		}
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
