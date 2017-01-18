/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:54:34 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/18 12:51:49 by lleverge         ###   ########.fr       */
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

static t_lexer			*create_lexer_node(char *str, int token_id)
{
	t_lexer		*new;
	int			i;

	i = 0;
	if (!(new = (t_lexer *)malloc(sizeof(t_lexer))))
		return (NULL);
	new->token_id = token_id;
	new->content = str;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int						get_token_id(char *str)
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
	else if (!ft_strcmp(str, "||"))
		return (OR);
	else if (!ft_strcmp(str, "&&"))
		return (AND);
	else
		return (CMD);
	return (0);
}

t_lexer					*lexer_list(t_lexer *list, char *str)
{
	t_lexer		*new;
	int			token_id;

	token_id = get_token_id(str);
	new = create_lexer_node(str, token_id);
	if (new)
		lexer_pushb(&list, new);
	return (list);
}
