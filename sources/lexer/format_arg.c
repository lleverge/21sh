/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:49:35 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/18 19:41:13 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"
#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static int		parse_through(t_lexer **list, t_lexer *elem)
{
	t_lexer		*tmp;
	t_token_id	tok_value;

	tmp = *list;
	tok_value = tmp->token_id;
	tmp = tmp->next;
	while (tmp && tmp != elem)
	{
		if (tmp->token_id == tok_value)
		{
			*list = tmp;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int				is_quoted_lex(t_lexer *node, t_lexer *lexlist)
{
	t_lexer		*tmp;

	tmp = lexlist;
	while (tmp && tmp != node)
	{
		if (tmp->token_id == QUOTE || tmp->token_id == DQUOTE)
		{
			if (parse_through(&tmp, node))
				return (1);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

static int		ft_count_words(char const *s)
{
	int i;
	int nb_w;

	i = 0;
	nb_w = 0;
	while (s[i] != '\0')
	{
		if (s[i] != 32 && s[i] != '\n' && s[i] != '\t' && s[i])
		{
			nb_w++;
			while (s[i] != 32 && s[i] != '\n' && s[i] != '\t' && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (nb_w);
}

int				count_allwords(t_lexer *lex, t_lexer *lexlist)
{
	if (is_quoted_lex(lex, lexlist))
		return (1);
	return (ft_count_words(lex->content));
}

int				split_words(char *src, char **dest, int i)
{
	char	**tmp;
	char	**start;
	int		ret;

	start = NULL;
	start = ft_strsplit_ws(src);
	tmp = start;
	ret = 0;
	while (*tmp)
	{
		dest[i] = ft_strdup(*tmp);
		tmp++;
		i++;
		ret++;
	}
	start ? free_tab(start) : NULL;
	return (ret);
}
