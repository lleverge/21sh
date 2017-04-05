/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 15:00:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/25 15:41:50 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

char		**parser(t_lexer *list)
{
	char	**cmd;
	t_lexer	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = list;
	while (tmp->token_id == CMD && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (!(cmd = (char **)malloc(sizeof(char *) * i + 1)))
	{
		ft_putendl_fd("error: parser malloc failed", 2);
		exit(-1);
	}
	while (j < i)
	{
		cmd[j] = ft_strdup(list->content);
		list = list->next;
		j++;
	}
	cmd[j] = NULL;
	return (cmd);
}
