/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_arg_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:53:28 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/18 12:12:30 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static int				count_words(t_lexer *lex)
{
	t_lexer *tmp;
	int 	ret;

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

// char			**cmd_format(char *cmd)
// {
// 	t_lexer		*lexer;
// 	t_lexer 	*tmp;
// 	t_lexer		*safe;
// 	char		**dest;
// 	int			i;

// 	lexer = init_lexer(cmd);
// 	lexer = merge_token(lexer);
// 	if (!(dest = (char **)malloc(sizeof(char *) * (count_words(lexer) + 1))))
// 	{
// 		free_lexer(&lexer);
// 		ft_putendl("cmd_format returns NULL");
// 		return (NULL);
// 	}
// 	i = 0;
// 	tmp = lexer;
// 	while (tmp)
// 	{
// 		if (tmp->token_id == TOK_WORD)
// 		{
// 			safe = tmp;
// 			if (is_quoted_lex(tmp, lexer))
// 			{
// 				tmp = safe;
// 				dest[i] = ft_strdup(tmp->content);
// 				i++;
// 			}
// 			else
// 				i += split_words(tmp->content, dest, i);
// 		}
// 		tmp = tmp->next;
// 	}
// 	dest[i] = NULL;
// 	free_lexer(&lexer);
// 	return (dest);
// }

static	char	**empty_exception(t_lexer *lex)
{
	char		**dest;

	dest = NULL;
	if (!(dest = (char **)malloc(sizeof(char *) * 2)))
	{
		ft_putendl_fd("21sh : malloc error, abort", 2);
		exit(3);
	}
	dest[0] = ft_strdup("");
	dest[1] = NULL;
	lex_free_all(lex);
	return (dest);
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

char		**cmd_format(char *base)
{
	t_lexer		*lexer;
	char		**dest;

	lexer = merge_token(init_lexer(base));
	if (!count_words(lexer))
		return (empty_exception(lexer));
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