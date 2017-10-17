/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:54:34 by lleverge          #+#    #+#             */
/*   Updated: 2017/04/06 15:43:37 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

static void				lexer_pushb(t_lexer **list, t_lexer *new)
{
	t_lexer		*tmp;

	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

static t_lexer			*create_lexer_node(char *str, char **cmd)
{
	t_lexer		*new;
	int			i;

	i = 0;
	if (!(new = (t_lexer *)malloc(sizeof(t_lexer))))
		return (NULL);
	new->token_id = 0;
	new->content = str;
	new->cmd = ft_tabdup(cmd);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_lexer					*lexer_list(t_lexer *list, char *str, char **cmd)
{
	t_lexer		*new;

	new = create_lexer_node(str, cmd);
	if (new)
		lexer_pushb(&list, new);
	return (list);
}
