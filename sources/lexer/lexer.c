/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/18 19:35:40 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static int					test_token_id(char *str)
{
	if (!ft_strcmp(str, ">>"))
		return (DGREAT);
	else if (!ft_strcmp(str, "<<"))
		return (DLESS);
	else if (ft_cntc(str, '>') == 1)
		return (GREAT);
	else if (ft_cntc(str, '<') == 1)
		return (LESS);
	else if (ft_cntc(str, '>') == 2)
		return (DGREAT);
	else if (ft_cntc(str, '<') == 2)
		return (DLESS);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (0);
}

static void					get_token_id(char *cmd, t_lexer *list)
{
	int		i;
	int		id;
	char	**tmp;

	i = 0;
	tmp = ft_strsplit_ws(cmd);
	while (tmp[i])
	{
		if ((id = test_token_id(tmp[i])) > 0)
		{
			list->token_id = id;
			list = list->next;
		}
		i++;
	}
	list->token_id = SEPARATOR;
}

t_lexer		*lexer(char *cmd, t_ult *ult)
{
	char		**cmd2;
	t_lexer		*list;
	int			i;

	i = 0;
	list = NULL;
	cmd2 = ft_strsplit_tok(cmd);
	ft_strlen(ult->path[0]);
	while (cmd2[i])
	{
		list = lexer_list(list, cmd2[i]);
		i++;
	}
	get_token_id(cmd, list);
	//exe_fork(ult->env, cmd2, path_in_tab(ult->env, cmd2));
	free_tab(cmd2);
	return (list);
}
