/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 14:41:54 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/27 13:03:01 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static int	empty_word(char *word)
{
	char	*tmp;

	tmp = word;
	while (*tmp)
	{
		if (*tmp > 32 && *tmp < 127)
			return (0);
		tmp++;
	}
	return (1);
}

static int	empty_words(t_lexer	*lexlist)
{
	t_lexer	*tmp;

	tmp = lexlist;
	while (tmp)
	{
		if (!empty_word(tmp->content))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static int	prompt_needed(t_lexer *lexlist)
{
	t_lexer	*tmp;

	tmp = lexlist;
	while (tmp)
	{
		if (tmp->token_id == PIPE)
		{
			if (!tmp->next || empty_words(tmp->next))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static t_lexer		*read_until_closed_pipe(t_ult *ult, t_lexer *lexlist)
{
	t_lexer	*lex_end;
	char	*dest;
	int		ret;

	lex_end = NULL;
	dest = NULL;
	while (42)
	{
		if (!(dest = termcaps_heredoc(ult)))
		{
			lex_free_all(lexlist);
			return (NULL);
		}
		lex_end = init_lexer(dest);
		lex_push(lex_end, &lexlist);
		if (!(ret = prompt_needed(lexlist)))
			break ;
		dest ? ft_strdel(&dest) : NULL ;
	}
	dest ? ft_strdel(&dest) : NULL ;
	return (lexlist);
}

t_lexer		*prompt_pipe(t_lexer *lex, t_ult *ult)
{
	if (!prompt_needed(lex))
		return (lex);
	return(read_until_closed_pipe(ult, lex));
}
