/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:00:54 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 16:08:17 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

static char		*get_word_string(t_lexer *merge_start, int to_merge)
{
	char		*dest;
	t_lexer		*tmp;

	dest = NULL;
	tmp = merge_start;
	dest = ft_strdup("");
	tmp = tmp->next;
	while (to_merge > 0)
	{
		dest = ft_strjoin_free_one(&dest, tmp->content);
		tmp = tmp->next;
		to_merge--;
	}
	return (dest);
}

static void		do_merge(t_lexer *merge_start, int to_merge, char *word)
{
	t_lexer		*new;
	t_lexer		*tmp;
	t_lexer		*tmp2;

	new = create_lexer_node(word);
	new->token_id = TOK_WORD;
	tmp = merge_start->next;
	while (to_merge > 0)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		lex_free_one(tmp2);
		to_merge--;
	}
	new->next = tmp;
	tmp->prev = new;
	new->prev = merge_start;
	merge_start->next = new;
}

int				count_merge_token(t_lexer *lex)
{
	t_lexer		*tmp;
	int			to_merge;
	t_token_id	quote_val;

	to_merge = 0;
	tmp = lex;
	while (tmp)
	{
		if (tmp->token_id == DQUOTE || tmp->token_id == QUOTE)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	quote_val = tmp->token_id;
	tmp = tmp->next;
	while (tmp && tmp->token_id != quote_val)
	{
		to_merge++;
		tmp = tmp->next;
	}
	return (to_merge);
}

t_lexer			*merge_token(t_lexer *lex)
{
	int			to_merge;
	char		*new_word;
	t_lexer		*tmp;

	new_word = NULL;
	if (!(to_merge = count_merge_token(lex)))
		return (lex);
	tmp = lex;
	while (tmp)
	{
		if (tmp->token_id == DQUOTE || tmp->token_id == QUOTE)
			break ;
		tmp = tmp->next;
	}
	new_word = get_word_string(tmp, to_merge);
	do_merge(tmp, to_merge, new_word);
	ft_strdel(&new_word);
	return (lex);
}
