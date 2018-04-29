/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dquoted.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 16:32:31 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/29 16:50:36 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int				is_dquoted(t_lexer *node, t_lexer *lexlist)
{
	t_lexer		*tmp;

	tmp = lexlist;
	if (!lexlist || !node)
		return (0);
	while (tmp && tmp != node)
	{
		if (tmp->token_id == DQUOTE)
		{
			tmp = tmp->next;
			while (tmp && tmp->token_id != DQUOTE)
			{
				if (tmp == node)
					return (1);
				tmp = tmp->next;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

int				is_squoted(t_lexer *node, t_lexer *lexlist)
{
	t_lexer		*tmp;

	tmp = lexlist;
	if (!lexlist || !node)
		return (0);
	while (tmp && tmp != node)
	{
		if (tmp->token_id == QUOTE)
		{
			tmp = tmp->next;
			while (tmp && tmp->token_id != QUOTE)
			{
				if (tmp == node)
					return (1);
				tmp = tmp->next;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}
