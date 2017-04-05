/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/04/05 20:12:56 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

t_lexer		*lexer(char *cmd, t_ult *ult)
{
	char		**cmd2;
	t_lexer		*list;
	int			i;

	i = 0;
	list = NULL;
	cmd2 = ft_strsplit_ws(cmd);
	while (cmd2[i])
	{
		list = lexer_list(list, cmd2[i], cmd2);
		i++;
	}
	do_pipe(ult, list);
//	exe_fork(ult->env, cmd2, path_in_tab(ult->env, cmd2));
	free_tab(cmd2);
	return (list);
}
