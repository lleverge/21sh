/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 11:36:00 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/30 11:55:20 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void		apply_expand(t_lexer *lex, t_ult *ult)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->token_id == TOK_WORD && !is_squoted(tmp, lex))
			tmp = expand_var(tmp, ult);
		tmp = tmp->next;
	}
}
