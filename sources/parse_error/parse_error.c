/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:17:33 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/18 18:41:43 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static int		print_parse_error(t_lexer *tmp, int error_fd)
{
	if (tmp->token_id < 12 && tmp->token_id != QUOTE &&
		tmp->token_id != DQUOTE && !tmp->next)
	{
		ft_putendl_fd("21sh: parse error near '\\n'", error_fd);
		return (-1);
	}
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

int				parse_error(t_lexer *lex, int error_fd)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (print_parse_error(tmp, error_fd) == -1)
			return (-1);
		else if ((tmp->token_id == 3 && LNEXT && LNEXT->token_id == 3 &&
				LDNEXT && LDNEXT->token_id < 13) || (tmp->token_id == 2
				&& LNEXT->token_id == 2 && LDNEXT && LDNEXT->token_id < 13) ||
				(tmp->token_id == 0 && LNEXT->token_id == 3 && LDNEXT &&
				LDNEXT->token_id < 13) || (tmp->token_id == 3 && LNEXT->token_id
				== 0 && LDNEXT && LDNEXT->token_id < 13) || ((tmp->token_id == 3
				|| tmp->token_id == 2 || tmp->token_id == 0) && LNEXT->token_id
				== SEPARATOR) || ((tmp->token_id == 0) && (LNEXT->token_id
				== 0)) || ((!LPREV || LPREV->token_id != 14) && tmp->token_id
				== 12 && !tmp->next) || (tmp->token_id == 1 && LNEXT &&
				LNEXT->token_id != 14))
		{
			print_parse_error2(tmp, error_fd);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
