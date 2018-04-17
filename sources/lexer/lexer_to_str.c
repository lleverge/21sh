/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:10:39 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/17 16:32:53 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"
#include "../../includes/cmd_edit.h"

t_lexer		*lexdup(t_lexer *lexlist)
{
	t_lexer	*new;

	if (!lexlist)
		return (NULL);
	new = create_lexer_node(lexlist->content);
	new->token_id = lexlist->token_id;
	new->prev = lexlist->prev;
	new->next = lexdup(lexlist->next);
	return (new);
}

char		*lexer_to_str(t_lexer *lex)
{
	t_lexer *tmp;
	char	*dest;

	tmp = lex;
	dest = NULL;
	while (tmp)
	{
		dest = !dest ? ft_strdup(tmp->content) :
			ft_strjoin_free_one(&dest, tmp->content);
		tmp = tmp->next;
	}
	return (dest);
}
