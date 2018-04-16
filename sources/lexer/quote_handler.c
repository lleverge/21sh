/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:38:13 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/16 19:52:21 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"
#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static int		is_closed(t_lexer *lex)
{
	t_lexer		*tmp;
	int			tok_id;

	tmp = lex;
	while (tmp && tmp->token_id != DQUOTE && tmp->token_id != QUOTE)
		tmp = tmp->next;
	tok_id = tmp->token_id;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->token_id == tok_id)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static t_lexer	*get_start_node(t_lexer *lex)
{
	t_lexer		*start;

	start = lex;
	while (start)
	{
		if (start->token_id == QUOTE || start->token_id == DQUOTE)
		{
			if (!is_closed(start))
				return (start);
		}
		start = start->next;
	}
	return (start);
}

static char		*get_new_word(t_lexer *start)
{
	t_lexer		*tmp;
	char		*buff;

	tmp = start;
	buff = NULL;
	tmp = tmp->next;
	while (tmp)
	{
		if (!buff)
			buff = ft_strdup(tmp->content);
		else
			buff = ft_strjoin_free_one(&buff, tmp->content);
		tmp = tmp->next;
	}
	return (buff);
}

void			get_final_string(t_lexer **lexlist, char **buffer)
{
	char		*dest;
	t_lexer		*start;
	t_lexer		*new;

	dest = NULL;
	start = NULL;
	if (!(start = get_start_node(*lexlist)))
		return ;
	dest = get_new_word(start);
	if (dest && !ft_strchr(dest, '\n'))
		dest = ft_strjoin_free_one(&dest, "\n");
	if (dest)
		dest = ft_strjoin_free_one(&dest, *buffer);
	else
		dest = ft_strdup(*buffer);
	new = new_word_init(&dest, start->token_id);
	if (start->next && new)
		free_lexer(&start->next);
	lex_push(new, lexlist);
	new->prev = start;
	ft_strdel(&dest);
	new = end_prompted_extract(buffer, start->token_id);
	lex_push(new, lexlist);
}
