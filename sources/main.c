/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:50:10 by vfrolich          #+#    #+#             */
/*   Updated: 2018/02/14 17:29:28 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>
#include <cmd_edit.h>
#include <stdio.h>

void type_lex_print(t_token_id tok_id)
{
	if (tok_id == 0)
		ft_putendl("SAND");
	if (tok_id == 1)
		ft_putendl("PIPE");
	if (tok_id == 2)
		ft_putendl("LESS");
	if (tok_id == 3)
		ft_putendl("GREAT");
	if (tok_id == 4)
		ft_putendl("DGREAT");
	if (tok_id == 5)
		ft_putendl("DLESS");
	if (tok_id == 6)
		ft_putendl("QUOTE");
	if (tok_id == 7)
		ft_putendl("DQUOTE");
	if (tok_id == 8)
		ft_putendl("AND");
	if (tok_id == 9)
		ft_putendl("OR");
	if (tok_id == 11)
		ft_putendl("AGGRG");
	if (tok_id == 12)
		ft_putendl("SEPARATOR");
	if (tok_id == 13)
		ft_putendl("NEWLINE");
	if (tok_id == 14)
		ft_putendl("TOK_WORD");
}

void lex_print(t_lexer *lexlist)
{
	t_lexer *tmp;

	tmp = lexlist;
	while (tmp)
	{
		ft_putstr("token id is ->");
		type_lex_print(tmp->token_id);
		ft_putstr("token value is->");
		ft_putstr(tmp->content);
		ft_putendl("<-");
		ft_putendl("-----------------------------------------------------");
		tmp = tmp->next;
	}
}

void	lex_r_print(t_lexer *lexlist)
{
	t_lexer *tmp;

	tmp = lexlist;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		ft_putstr("token id is ->");
		type_lex_print(tmp->token_id);
		ft_putstr("token value is->");
		ft_putstr(tmp->content);
		ft_putendl("<-");
		ft_putendl("-----------------------------------------------------");
		tmp = tmp->prev;
	}
}

void	job_print(t_job *jobs)
{
	t_job *tmp;
	t_process *tmp2;

	tmp = jobs;
	while (tmp)
	{
		ft_putstr("new job ->");
		tmp2 = tmp->proc; 
		while (tmp2)
		{
			ft_putstr("proc cmd->");
			ft_putendl(tmp2->cmd);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}


int				init_all(char **environ)
{
	t_ult		*ult;
	t_lexer		*lex;
	t_job 		*jobs;

	ult = NULL;
	jobs = NULL;
	ult = init_ult(ult, environ);
	lex = NULL;
	while (42)
	{
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
			// job_print(jobs);
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
