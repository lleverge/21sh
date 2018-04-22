/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:28:40 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/22 16:50:07 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

int		parse_pipe(t_lexer *lex)
{
	t_lexer *tmp;

	tmp = lex;
	if (tmp->token_id == PIPE && LNEXT && (LNEXT->token_id == SEPARATOR ||
	LNEXT->token_id == GREAT || LNEXT->token_id == LESS ||
	LNEXT->token_id == PIPE || LNEXT->token_id == SAND))
		return (1);
	else if ((tmp->token_id == PIPE && !LNEXT) || (tmp->token_id ==
			PIPE && LNEXT && !LDNEXT && is_full_spaces(LNEXT->content)))
		return (1);
	else if (tmp->token_id == PIPE && LNEXT && LDNEXT &&
			is_full_spaces(LNEXT->content) && (LDNEXT->token_id ==
			SEPARATOR || LDNEXT->token_id == LESS ||
			LDNEXT->token_id == GREAT || LDNEXT->token_id
			== SAND || LDNEXT->token_id == PIPE))
		return (1);
	else
		return (0);
}

int		parse_and(t_lexer *lex)
{
	t_lexer *tmp;

	tmp = lex;
	if (tmp->token_id == SAND && !LNEXT)
		return (1);
	else if (tmp->token_id == PIPE && LNEXT && !LDNEXT
			&& is_full_spaces(LNEXT->content))
		return (1);
	else if (tmp->token_id == SAND && LNEXT &&
			tmp->prev && (tmp->prev->token_id != GREAT
			|| ft_strncmp(LNEXT->content, "-", 1)))
		return (1);
	else
		return (0);
}
