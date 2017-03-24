/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:31:24 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/24 16:34:57 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int			lexer_error(t_lexer *list)
{
	if (list->token_id >= 0 && list->token_id <= 4)
		return (-1);
	while (list->next)
		list = list->next;
	if (list->token_id == PIPE)
		return (-1);
	return (0);
}
