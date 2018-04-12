/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:54:34 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/12 16:17:27 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

void			lex_free_all(t_lexer *lexlist)
{
	t_lexer		*tmp;

	tmp = lexlist->next;
	lex_free_one(lexlist);
	while (tmp)
	{
		lexlist = tmp;
		tmp = lexlist->next;
		lex_free_one(lexlist);
	}
	lexlist = NULL;
}

void			lex_free_one(t_lexer *lexnode)
{
	ft_strdel(&lexnode->content);
	free(lexnode);
	lexnode = NULL;
}

static void		lexer_pushb(t_lexer **list, t_lexer *new)
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

t_lexer			*create_lexer_node(char *str)
{
	t_lexer		*new;
	int			i;

	i = 0;
	if (!(new = (t_lexer *)malloc(sizeof(t_lexer))))
	{
		ft_putendl_fd("21sh: mem alloc error for t_lexer type, abort.",
			STDERR_FILENO);
		exit(1);
	}
	new->token_id = -1;
	new->content = ft_strdup(str);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_lexer			*lexer_list(t_lexer *list, char *str)
{
	t_lexer		*new;

	new = create_lexer_node(str);
	if (new)
		lexer_pushb(&list, new);
	return (list);
}
