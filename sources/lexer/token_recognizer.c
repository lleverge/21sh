/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 10:40:32 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/18 19:45:13 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int			fine_token(int token_id)
{
	if (token_id == SAND || token_id == SEPARATOR || token_id == PIPE)
		return (1);
	return (0);
}

int			is_token_char(char c)
{
	if (!c)
		return (0);
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '|' || c == '\''
		|| c == '"' || c == ';' || c == '\n')
		return (1);
	return (0);
}

t_token_id	which_token(char c)
{
	if (c == '&')
		return (SAND);
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (LESS);
	if (c == '>')
		return (GREAT);
	if (c == '\'')
		return (QUOTE);
	if (c == '"')
		return (DQUOTE);
	if (c == ';')
		return (SEPARATOR);
	if (c == '\n')
		return (NEWLINE);
	return (TOK_WORD);
}
