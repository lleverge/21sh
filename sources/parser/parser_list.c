/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:39:47 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/24 19:14:20 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void					free_parser(t_parser **head)
{
	t_parser	*next;

	while (*head)
	{
		next = (*head)->next;
		free_tab((*head)->content);
		free(*head);
		*head = next;
	}
}

static void				parser_pushb(t_parser **head, t_parser *new)
{
	t_parser *cur;

	if (!*head)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

static t_parser			*create_parser(t_lexer *list, int token_id)
{
	t_parser	*new;
	int			i;

	i = 0;
	if (!(new = (t_parser *)malloc(sizeof(t_parser))))
	{
		ft_putendl_fd("error: parser malloc failed", 2);
		exit(-1);
	}
	if (!(new->content = (char **)malloc(sizeof(char *) * (count_tablen(list->cmd) + 1))))
	{
		ft_putendl_fd("error: parser malloc failed", 2);
		exit(-1);
	}
	while (list->cmd[i])
	{
		new->content[i] = ft_strdup(list->cmd[i]);
		i++;
	}
	new->content[i] = NULL;
	new->token = token_id;
	new->stdin = 0;
	new->stdout = 1;
	new->shutout_in = 0;
	new->shutout_out = 0;
	new->next = NULL;
	return (new);
}

t_parser				*fill_parser(t_parser *list, t_lexer *list_lex, int token)
{
	parser_pushb(&list, create_parser(list_lex, token));
	return (list);
}
