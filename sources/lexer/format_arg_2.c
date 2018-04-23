/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_arg_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:53:28 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/23 17:51:56 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static int		count_words(t_lexer *lex)
{
	t_lexer	*tmp;
	int		ret;

	ret = 0;
	tmp = lex;
	while (tmp)
	{
		if (tmp->token_id == TOK_WORD)
			ret += count_allwords(tmp, lex);
		tmp = tmp->next;
	}
	return (ret);
}

static void		fill_dest(char **dest, t_lexer *lexer)
{
	t_lexer	*tmp;
	t_lexer	*safe;
	int		i;

	i = 0;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->token_id == TOK_WORD)
		{
			safe = tmp;
			if (is_quoted_lex(tmp, lexer))
			{
				tmp = safe;
				dest[i] = ft_strdup(tmp->content);
				i++;
			}
			else
				i += split_words(tmp->content, dest, i);
		}
		tmp = tmp->next;
	}
	dest[i] = NULL;
}

// static void 	lex_type(int type)
// {

// 	if (type == QUOTE)
// 		ft_putstr("QUOTE");
// 	if (type == DQUOTE)
// 		ft_putstr("DQUOTE");
// 	if (type == GREAT)
// 		ft_putstr("GREAT");
// 	if (type == LESS)
// 		ft_putstr("LESS");
// 	if (type == DGREAT)
// 		ft_putstr("DGREAT");
// 	if (type == DLESS)
// 		ft_putstr("DLESS");
// 	if (type == AGGREG)
// 		ft_putstr("AGGREG");
// 	if (type == AND)
// 		ft_putstr("AND");
// 	if (type == OR)
// 		ft_putstr("OR");
// 	if (type == SEPARATOR)
// 		ft_putstr("SEPARATOR");
// 	if (type == NEWLINE)
// 		ft_putstr("NEWLINE");
// 	if (type == TOK_WORD)
// 		ft_putstr("TOK_WORD");
// }


// static void lex_print(t_lexer *lex)
// {
// 	t_lexer *tmp;

// 	tmp = lex;
// 	while (tmp)
// 	{
// 		ft_putstr(tmp->content);
// 		ft_putstr(" TYPE IS :");
// 		lex_type(tmp->token_id);
// 		ft_putendl("");
// 		tmp = tmp->next;
// 	}
// }

char			**cmd_format(char *base)
{
	t_lexer		*lexer;
	char		**dest;

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
