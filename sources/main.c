/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/19 12:48:52 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>
#include <cmd_edit.h>

int				fill_lexer(char **cmd, t_lexer *list, t_ult *ult)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		list = lexer(cmd[i], ult);
		i++;
	}
	return (0);
}

int				init_all(char **environ)
{
	t_ult		*ult;
	t_process	*proc;
	char		**cmd;
	t_lexer		*list;
	int			i;

	ult = NULL;
	proc = NULL;
	list = NULL;
	ult = init_ult(ult, environ);
	while (42)
	{
		i = 0;
		get_prompt(ult->env);
		termcap(ult);
		ft_putchar('\n');
		cmd = ft_strsplit(ult->cmd, ';');
		fill_lexer(cmd, list, ult);
		while (list)
		{
			printf("list->content = %s\ntoken = %i\n", list->content, list->token_id);
			list = list->next;
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
