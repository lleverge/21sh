/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/24 15:32:28 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void		lexer(char *cmd)
{
	char		**cmd2;
	t_lexer		*list;
	int			i;

	i = 0;
	list = NULL;
	cmd2 = ft_strsplit_ws(cmd);
	while (cmd2[i])
	{
		list = lexer_list(list, cmd2[i]);
		i++;
	}
	free_lexer(&list);
	free_tab(cmd2);
}
