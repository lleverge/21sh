/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errortools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 19:17:48 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/19 17:50:48 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

int		is_parse_error(t_lexer *lex)
{
	t_lexer		*tmp;

	tmp = lex;
	if ((tmp->token_id < 12 && tmp->token_id != 6 && tmp->token_id != 7
	&& !LNEXT) || (tmp->token_id == 12 && !LPREV) || (tmp->token_id < 12
	&& tmp->token_id != 6 && tmp->token_id != 7 && !LNEXT)
	|| (tmp->token_id == 1 && LNEXT && LNEXT->token_id != 14) ||
	(tmp->token_id == 2 && LNEXT->token_id != 2 && LNEXT->token_id != 0
	&& LNEXT->token_id != 6 && LNEXT->token_id != 7) ||
	(tmp->token_id == 3 && LNEXT->token_id != 3 && LNEXT->token_id != 0 &&
	LNEXT->token_id != 6 && LNEXT->token_id != 7) || (tmp->token_id == 12 &&
	LNEXT && LNEXT->token_id == 12))
	{
		return (0);
	}
	else
		return (1);
}

int		is_full_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
