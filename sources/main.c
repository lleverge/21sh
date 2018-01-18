/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:50:10 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/18 21:45:46 by vfrolich         ###   ########.fr       */
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

// void type_lex_print(t_token_id tok_id)
// {
// 	if (tok_id == 1)
// 		ft_putendl("PIPE");
// 	if (tok_id == 2)
// 		ft_putendl("LESS");
// 	if (tok_id == 3)
// 		ft_putendl("GREAT");
// 	if (tok_id == 4)
// 		ft_putendl("DGREAT");
// 	if (tok_id == 5)
// 		ft_putendl("DLESS");
// 	if (tok_id == 6)
// 		ft_putendl("QUOTE");
// 	if (tok_id == 7)
// 		ft_putendl("DQUOTE");
// 	if (tok_id == 8)
// 		ft_putendl("AND");
// 	if (tok_id == 9)
// 		ft_putendl("OR");
// 	if (tok_id == 11)
// 		ft_putendl("AGGRG");
// 	if (tok_id == 12)
// 		ft_putendl("SEPARATOR");
// 	if (tok_id == 13)
// 		ft_putendl("NEWLINE");
// 	if (tok_id == 14)
// 		ft_putendl("TOK_WORD");
// }

// void lex_print(t_lexer *lexlist)
// {
// 	t_lexer *tmp;

// 	tmp = lexlist;
// 	while (tmp)
// 	{
// 		ft_putstr("token id is ->");
// 		type_lex_print(tmp->token_id);
// 		ft_putstr("token value is->");
// 		ft_putstr(tmp->content);
// 		ft_putendl("<-");
// 		ft_putendl("-----------------------------------------------------");
// 		tmp = tmp->next;
// 	}
// }

// void	lex_r_print(t_lexer *lexlist)
// {
// 	t_lexer *tmp;

// 	tmp = lexlist;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	while (tmp)
// 	{
// 		ft_putstr("token id is ->");
// 		type_lex_print(tmp->token_id);
// 		ft_putstr("token value is->");
// 		ft_putstr(tmp->content);
// 		ft_putendl("<-");
// 		ft_putendl("-----------------------------------------------------");
// 		tmp = tmp->prev;
// 	}
// }

int				init_all(char **environ)
{
	t_ult		*ult;
	// t_lexer		*lex;

	ult = NULL;
	ult = init_ult(ult, environ);
	while (42)
	{
		get_prompt(ult->env);
		termcap(ult);
		ft_putchar('\n');
		// if (ult->cmd)
		// {
		// 	lex = init_lexer(ult->cmd);
		// 	lex = quote_tok(lex, ult);
		// 	lex_print(lex);
		// 	lex = merge_token(lex);
		// 	lex_print(lex);
		// }
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
