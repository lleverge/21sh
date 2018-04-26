/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:28:40 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/26 21:55:31 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

int		parse_first(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	if ((tmp->token_id < 13 && tmp->token_id != SEPARATOR && tmp->token_id
		!= QUOTE && tmp->token_id != DQUOTE && !LNEXT) || (tmp->token_id ==
		SEPARATOR && (!tmp->prev || (is_full_spaces(tmp->prev->content)
		&& !tmp->prev->prev))) || (tmp->token_id == PIPE && !tmp->prev)
		|| (tmp->token_id == PIPE && tmp->prev &&
		is_full_spaces(tmp->prev->content) && !tmp->prev->prev))
		return (1);
	else
		return (0);
}

int		parse_pipe(t_lexer *lex)
{
	t_lexer *tmp;

	tmp = lex;
	if (tmp->token_id == PIPE && LPREV && LPREV->token_id == GREAT)
		return (1);
	if (tmp->token_id == PIPE && LNEXT && (LNEXT->token_id == SEPARATOR ||
	LNEXT->token_id == PIPE || LNEXT->token_id == SAND))
		return (1);
	else if ((tmp->token_id == PIPE && !LNEXT) || (tmp->token_id ==
			PIPE && LNEXT && !LDNEXT && is_full_spaces(LNEXT->content)))
		return (1);
	else if (tmp->token_id == PIPE && LNEXT && LDNEXT &&
			is_full_spaces(LNEXT->content) && (LDNEXT->token_id ==
			SEPARATOR || LDNEXT->token_id == SAND ||
			LDNEXT->token_id == PIPE))
		return (1);
	else
		return (0);
}

int		parse_and(t_lexer *lex)
{
	t_lexer *tmp;

	tmp = lex;
	if (tmp->token_id == SAND && (!LNEXT || !LPREV ||
	(is_full_spaces(LPREV->content) && !LPREV->prev)))
		return (1);
	else if (tmp->token_id == SAND && LNEXT && is_full_spaces(LNEXT->content) &&
			 LDNEXT && LDNEXT->token_id == 13)
		return (1);
	else if (tmp->token_id == SAND && LNEXT && tmp->prev && tmp->prev->token_id
			== GREAT && LNEXT->token_id == 14)
		return (0);
	else if (tmp->token_id == AND && LNEXT && !LDNEXT
			&& is_full_spaces(LNEXT->content))
		return (1);
	else if (tmp->token_id == SAND && LNEXT &&
			tmp->prev && (tmp->prev->token_id != GREAT
			|| ft_strncmp(LNEXT->content, "-", 1)))
		return (1);
	else
		return (0);
}
