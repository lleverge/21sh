/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/20 11:19:24 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>
#include <cmd_edit.h>

static int		parse_error(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[ft_strlen(cmd) - 1] == '&' && cmd[ft_strlen(cmd) - 2] != '&')
	{
		ft_putendl("21sh: & not accepted");
		return (-1);
	}
	while (cmd[i])
	{
		while (ft_isspace(cmd[i]))
			i++;
		if (ft_istoken(cmd[i]))
		{
			ft_putstr_fd("21sh: parse error near ", 2);
			ft_putchar_fd(cmd[i], 2);
			ft_putchar_fd('\n', 2);
			return (-1);
		}
		else
			return (0);
	}
	return (0);
}

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
		if (cmd[i] && parse_error(cmd[i]) == 0)
		{
			while (cmd[i])
			{
				new_lexer(cmd[i]);
				i++;
			}
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
