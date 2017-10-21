/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/21 17:20:06 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>
#include <cmd_edit.h>

static int		parse_error(char *cmd)
{
	int		i;

	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (ft_istoken(cmd[i]) > 0)
	{
		ft_putstr_fd("21sh: parse error near ", 2);
		ft_putchar_fd(cmd[i], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (0);
}

static int		full_parse_error(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (parse_error(cmd[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int				init_all(char **environ)
{
	t_ult		*ult;
	t_process	*proc;
	char		**cmd;
	char		*nosp;
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
		if (cmd[i])
		{
			if (full_parse_error(cmd) == 0)
			{
				while (cmd[i])
				{
					nosp = ft_strnosp(cmd[i]);
					new_lexer(nosp);
					ft_strdel(&nosp);
					i++;
				}
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
