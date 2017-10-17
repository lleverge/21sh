/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 08:34:11 by lleverge          #+#    #+#             */
/*   Updated: 2017/04/06 12:18:22 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

void			free_parser(t_parser **start)
{
	t_parser	*next;

	while (*start)
	{
		next = (*start)->next;
		free_tab((*start)->content);
		free(*start);
		*start = next;
	}
}

static void		parser_push_back(t_parser **start, t_parser *new)
{
	t_parser *cur;

	if (!*start)
		*start = new;
	else
	{
		cur = *start;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

static t_parser	*parser_create_node(int token)
{
	t_parser	*new;
	int			i;

	i = 0;
	if (!(new = (t_parser *)malloc(sizeof(t_parser))))
	{
		ft_putendl_fd("error: parser malloc failed", 2);
		exit(-1);
	}
	new->content = NULL;
	new->token = token;
	new->stdin = 0;
	new->stdout = 1;
	new->shutin = 0;
	new->shutout = 0;
	new->next = NULL;
	return (new);
}

t_parser		*fill_parser(t_parser *list, int token)
{
	parser_push_back(&list, parser_create_node(token));
	return (list);
}
