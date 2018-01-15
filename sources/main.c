/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:50:10 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/15 19:40:18 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>
#include <cmd_edit.h>


static void setting_all(t_ult *ult)
{
	char **cmd;
	char **splited_cmd;
	char **tmp;

	cmd = NULL;
	splited_cmd = NULL;
	splited_cmd = ft_strsplit(ult->cmd, ';');
	tmp = splited_cmd;
	while (*tmp)
	{
		cmd = ft_strsplit_tok(*tmp);
		start_prog(ult, cmd);
		free_tab(cmd);
		tmp++;
	}
	free_tab(splited_cmd);
}

int				init_all(char **environ)
{
	t_ult		*ult;

	ult = NULL;
	ult = init_ult(ult, environ);
	while (42)
	{
		get_prompt(ult->env);
		termcap(ult);
		ft_putchar('\n');
		if (ult->cmd && *ult->cmd)
			setting_all(ult);
		ult->cmd ? ft_strdel(&ult->cmd) : NULL;
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
