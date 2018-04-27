/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_arg_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:53:28 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/27 14:38:15 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"
#include "../../includes/cmd_edit.h"

static char		*get_full_quote(t_lexer *lex, t_lexer *start)
{
	char		*dest;

	dest = NULL;
	dest = ft_strdup(lex->content);
	lex = lex->next;
	while (lex && is_quoted_lex(lex, start))
	{
		dest = ft_strjoin_free_one(&dest, lex->content);
		lex = lex->next;
	}
	return (dest);
}

static int		count_words(t_lexer *lex)
{
	t_lexer	*tmp;
	int		ret;

	ret = 0;
	tmp = lex;
	while (tmp)
	{
		if (tmp->token_id == TOK_WORD || is_quoted_lex(tmp, lex))
		{
			if (is_quoted_lex(tmp, lex))
			{
				ret++;
				while (is_quoted_lex(tmp, lex))
					tmp = tmp->next;
			}
			else
				ret += count_allwords(tmp, lex);
		}
		tmp ? tmp = tmp->next : NULL;
	}
	return (ret);
}

static void		fill_dest(char **dest, t_lexer *lexer)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->token_id == TOK_WORD || is_quoted_lex(tmp, lexer))
		{
			if (is_quoted_lex(tmp, lexer))
			{
				dest[i] = get_full_quote(tmp, lexer);
				i++;
				while (tmp && is_quoted_lex(tmp, lexer))
					tmp = tmp->next;
			}
			else
				i += split_words(tmp->content, dest, i);
		}
		if (tmp)
			tmp = tmp->next;
	}
	dest[i] = NULL;
}

char			**cmd_format(char *base)
{
	t_lexer		*lexer;
	char		**dest;

	if (!base)
		return (NULL);
	lexer = init_lexer(base);
	if (!count_words(lexer))
	{
		free_lexer(&lexer);
		return (NULL);
	}
	dest = NULL;
	if (!(dest = (char **)malloc(sizeof(char *) * (count_words(lexer) + 1))))
	{
		free_lexer(&lexer);
		return (NULL);
	}
	fill_dest(dest, lexer);
	free_lexer(&lexer);
	return (dest);
}
