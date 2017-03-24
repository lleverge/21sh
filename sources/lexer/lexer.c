/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/24 17:52:48 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

t_lexer		*lexer(char *cmd)
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
		list->cmd = ft_tabdup(cmd2);
		i++;
	}
	free_tab(cmd2);
	return (list);
}
