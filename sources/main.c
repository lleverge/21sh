/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:50:10 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/17 22:05:45 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include "../includes/lexer.h"
#include "../includes/cmd_edit.h"

int				init_all(char **environ)
{
	t_ult		*ult;
	t_lexer		*lex;
	t_job		*jobs;

	ult = NULL;
	jobs = NULL;
	ult = init_ult(ult, environ);
	lex = NULL;
	while (42)
	{
		main_signal_handler();
		get_prompt(ult->env);
		termcap(ult);
		ft_putchar('\n');
		if (ult->cmd && !is_blankword(ult->cmd))
		{
			lex = fill_lexer(ult);
			lex ? group_token(&lex) : NULL;
		}
		if (ult->cmd && *ult->cmd && lex)
		{
			jobs = set_jobs(lex);
			job_launch(jobs, ult);
			destroy_job_list(jobs);
		}
		lex ? lex_free_all(lex) : NULL;
		lex = NULL;
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
