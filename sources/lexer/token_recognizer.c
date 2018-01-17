/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 10:40:32 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/17 14:04:33 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int		is_token_char(char c)
{
	if (!c)
		return (0);
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '|' || c == '\''||
		c == '"' || c == ';' || c == '\n')
		return (1);
	return (0);
}

t_token_id	which_token(char c)
{
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
	if (c == '&' || c == ';')
		return (SEPARATOR);
	if (c == '\n')
		return (NEWLINE);
	return (TOK_WORD);
}
