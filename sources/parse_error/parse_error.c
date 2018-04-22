/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:17:33 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/22 20:07:23 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static int		parse_less(t_lexer *lex)
{
	t_lexer *tmp;

	tmp = lex;
	if (tmp->token_id == LESS && LNEXT && (LNEXT->token_id == SEPARATOR ||
	LNEXT->token_id == GREAT || LNEXT->token_id == PIPE ||
	LNEXT->token_id == SAND))
		return (1);
	else if ((tmp->token_id == LESS && LNEXT && LNEXT->token_id == LESS
			&& !LDNEXT) || (tmp->token_id == LESS && !LNEXT))
		return (1);
	else if ((tmp->token_id == LESS && LNEXT && LNEXT->token_id == LESS
			&& LDNEXT->token_id != 14))
		return (1);
	else if (tmp->token_id == LESS && LNEXT && LDNEXT &&
			is_full_spaces(LNEXT->content) && (LDNEXT->token_id ==
			SEPARATOR || LDNEXT->token_id == LESS ||
			LDNEXT->token_id == GREAT || LDNEXT->token_id
			== SAND || LDNEXT->token_id == PIPE))
		return (1);
	else
		return (0);
}

static int		parse_great(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	if (tmp->token_id == GREAT && LNEXT && (LNEXT->token_id == SEPARATOR ||
	LNEXT->token_id == LESS || LNEXT->token_id == PIPE))
		return (1);
	else if ((tmp->token_id == GREAT && LNEXT && LNEXT->token_id == GREAT
			&& !LDNEXT) || (tmp->token_id == GREAT && !LNEXT))
		return (1);
	else if (tmp->token_id == GREAT && LNEXT && LNEXT->token_id ==
			SAND && !LDNEXT)
		return (1);
	else if ((tmp->token_id == GREAT && LNEXT && LNEXT->token_id == GREAT
			&& LDNEXT->token_id != 14) && ((tmp->token_id == GREAT && LNEXT
			&& LDNEXT && LNEXT->token_id == SAND &&
			(ft_strncmp("-", LDNEXT->content, 1) || LDNEXT->token_id != 14))))
		return (1);
	else if (tmp->token_id == GREAT && LNEXT && LDNEXT &&
			is_full_spaces(LNEXT->content) && (LDNEXT->token_id ==
			SEPARATOR || LDNEXT->token_id == LESS ||
			LDNEXT->token_id == GREAT || LDNEXT->token_id
			== SAND || LDNEXT->token_id == PIPE))
		return (1);
	else
		return (0);
}

static void		print_parse_error2(t_lexer *tmp, int error_fd)
{
	ft_putstr_fd("21sh: parse error near '", error_fd);
	if (tmp->next)
		ft_putstr_fd(tmp->next->content, error_fd);
	else
		ft_putstr_fd(tmp->content, error_fd);
	ft_putendl_fd("'", error_fd);
}

static int		parse_separator(t_lexer *lex)
{
	t_lexer *tmp;

	tmp = lex;
	if ((tmp->token_id == SEPARATOR && !LNEXT) || (tmp->token_id == SEPARATOR
		&& LNEXT && !LDNEXT && is_full_spaces(LNEXT->content)))
		return (1);
	if (tmp->token_id == SEPARATOR && LNEXT && (LNEXT->token_id == SEPARATOR ||
	LNEXT->token_id == LESS || LNEXT->token_id == GREAT || LNEXT->token_id
	== SAND || LNEXT->token_id == PIPE))
		return (1);
	else if (tmp->token_id == SEPARATOR && LNEXT && LDNEXT &&
			is_full_spaces(LNEXT->content) && (LDNEXT->token_id == SEPARATOR
			|| LDNEXT->token_id == LESS || LDNEXT->token_id == GREAT ||
			LDNEXT->token_id == SAND || LDNEXT->token_id == PIPE))
		return (2);
	else
		return (0);
}

int				parse_error(t_lexer *lex, int error_fd)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (parse_separator(tmp) || parse_great(tmp) || parse_less(tmp)
			|| parse_and(tmp) || parse_pipe(tmp))
		{
			print_parse_error2(tmp, error_fd);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
