/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 14:41:54 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 16:07:11 by lleverge         ###   ########.fr       */
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

static int	prompt_needed(t_lexer *lexlist)
{
	t_lexer	*tmp;

	tmp = lexlist;
	while (tmp)
	{
		if (tmp->token_id == PIPE)
		{
			if (!tmp->next)
				return (1);
			if (empty_word(tmp->next->content) && !tmp->next->next)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_lexer		*prompt_pipe(t_lexer *lex, t_ult *ult)
{
	t_lexer	*lex_end;
	char	*dest;

	if (!prompt_needed(lex))
		return (lex);
	lex_end = NULL;
	dest = NULL;
	if (!(dest = termcaps_heredoc(ult)))
	{
		lex_free_all(lex);
		return (NULL);
	}
	while (empty_word(dest))
	{
		ft_strdel(&dest);
		if (!(dest = termcaps_heredoc(ult)))
		{
			lex_free_all(lex);
			return (NULL);
		}
	}
	lex_end = init_lexer(dest);
	lex_push(lex_end, &lex);
	dest ? ft_strdel(&dest) : NULL;
	return (lex);
}
