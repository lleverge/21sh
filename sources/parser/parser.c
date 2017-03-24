/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:00:08 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/24 19:10:37 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

t_parser		*do_parsing(t_ult *ult, t_lexer *list, t_parser *process)
{
	int ret;

	ret = 0;
	if (lexer_error(list) == -1)
		process = fill_parser(process, list, ERROR);
	else
		while (list)
		{
			if (list->token_id == CMD && list->next)
				process = fill_parser(process, list, list->next->token_id);
			if (list->token_id >= 1 && list->token_id <= 4)
				ret = manage_io_files(ult, list, process, list->token_id);
			if (ret == -1 || ret == -2)
			{
				free_parser(&process);
				break ;
			}
			else if (list->token_id == CMD && !list->next)
				process = fill_parser(process, list, END_LIST);
			list = list->next;
		}
	return (process);
}
