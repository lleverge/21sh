/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 12:28:37 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/30 14:40:54 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <shell.h>

static void		check_merge_aggreg2(t_lexer *lexer)
{
	t_lexer		*tmp;

	ft_strdel(&lexer->content);
	lexer->content = ft_strdup("&>");
	lexer->token_id = 11;
	tmp = lexer->next->next;
	lex_free_one(lexer->next);
	lexer->next = tmp;
	tmp->prev = lexer;
}

static void		check_merge_aggreg1(t_lexer *lexer)
{
	t_lexer		*tmp;

	ft_strdel(&lexer->content);
	lexer->content = ft_strdup(">&");
	lexer->token_id = 11;
	tmp = lexer->next->next;
	lex_free_one(lexer->next);
	lexer->next = tmp;
	tmp->prev = lexer;
}

static void		check_merge_dgreat(t_lexer *lexer)
{
	t_lexer		*tmp;

	ft_strdel(&lexer->content);
	lexer->content = ft_strdup(">>");
	lexer->token_id = 4;
	tmp = lexer->next->next;
	lex_free_one(lexer->next);
	lexer->next = tmp;
	tmp->prev = lexer;
}

static void		check_merge_dless(t_lexer *lexer)
{
	t_lexer		*tmp;

	ft_strdel(&lexer->content);
	lexer->content = ft_strdup("<<");
	lexer->token_id = 5;
	tmp = lexer->next->next;
	lex_free_one(lexer->next);
	lexer->next = tmp;
	tmp->prev = lexer;
}

void			group_token(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp)
	{
		if (tmp->token_id == 2 && tmp->next && tmp->next->token_id == 2)
			check_merge_dless(tmp);
		else if (tmp->token_id == 3 && tmp->next && tmp->next->token_id == 3)
			check_merge_dgreat(tmp);
		else if (tmp->token_id == 3 && tmp->next && tmp->next->token_id == 0)
			check_merge_aggreg1(tmp);
		else if (tmp->token_id == 0 && tmp->next && tmp->next->token_id == 3)
			check_merge_aggreg2(tmp);
		tmp = tmp->next;
	}
}
