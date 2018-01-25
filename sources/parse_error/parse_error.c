/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:17:33 by lleverge          #+#    #+#             */
/*   Updated: 2018/01/25 17:31:17 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

int			parse_error(t_lexer *lex, int error_fd)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->token_id < 12 && !tmp->next)
		{
			ft_putendl_fd("21sh: parse error near '\\n'", error_fd);
			return (-1);
		}
		else if ((tmp->token_id == 3 && LNEXT && LNEXT->token_id == 3 && LDNEXT && LDNEXT->token_id < 13) ||
				 (tmp->token_id == 2 && LNEXT->token_id == 2 && LDNEXT && LDNEXT->token_id < 13) ||
				 (tmp->token_id == 0 && LNEXT->token_id == 3 && LDNEXT && LDNEXT->token_id < 13) ||
				 (tmp->token_id == 3 && LNEXT->token_id == 0 && LDNEXT && LDNEXT->token_id < 13) ||
				 ((tmp->token_id == 3 || tmp->token_id == 2 || tmp->token_id == 0) && LNEXT->token_id == SEPARATOR))
		{
			ft_putstr_fd("21sh: parse error near '", error_fd);
			ft_putstr_fd(tmp->next->content, error_fd);
			ft_putendl_fd("'", error_fd);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
