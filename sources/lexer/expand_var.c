/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 17:36:00 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/30 11:35:01 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static char		*get_var_name(char *content)
{
	int			i;
	int			w_start;

	i = 0;
	w_start = 0;
	while (content[i] && content[i] != '$')
		i++;
	if (content[i + 1])
		i++;
	w_start = i;
	while (content[i] && ft_isalnum(content[i]))
		i++;
	if ((i - w_start) <= 0)
		return (NULL);
	return (ft_strsub(content, w_start, i - w_start));
}

static t_lexer	*expand_word(t_lexer *lex, t_ult *ult, char *word)
{
	int			index_start;
	char		*before;
	char		*after;

	index_start = ft_strchr(lex->content, '$') - lex->content;
	before = ft_strsub(lex->content, 0, index_start);
	after = ft_strsub(lex->content, index_start + ft_strlen(word) + 1,
	(ft_strlen(lex->content) - (index_start + ft_strlen(word) + 1)));
	before = ft_strjoin_free_one(&before, cpy_node_content(ult->env, word));
	before = ft_strjoin_free(&before, &after);
	ft_strdel(&lex->content);
	lex->content = before;
	return (lex);
}	

static t_lexer	*expand_it(t_lexer *lex, t_ult *ult)
{
	char 		*word;
	char		*new;

	if (!ult)
		return (NULL);
	word = NULL;
	if (!(word = get_var_name(lex->content)))
		return (lex);
	if (!cpy_node_content(ult->env, word))
	{
		ft_strdel(&word);
		word = get_del_string(lex->content);
		new = ft_extracter(lex->content, word);
		ft_strdel(&lex->content);
		word ? ft_strdel(&word) : NULL;
		lex->content = new;
		return (lex);
	}
	expand_word(lex, ult, word);
	word ? ft_strdel(&word) : NULL;
	return (lex);
}

static t_lexer	*expand_all(t_lexer *node, t_ult *ult)
{
	char		*tmp;

	tmp = NULL;
	while (ft_strchr(node->content, '$'))
	{
		tmp = get_var_name(node->content);
		if (!tmp)
			break ;
		node = expand_it(node, ult);
		ft_strdel(&tmp);
	}
	return (node);
}

t_lexer			*expand_var(t_lexer *lex, t_ult *ult)
{
	t_lexer		*node;

	node = lex;
	while (node)
	{
		if (node->token_id == TOK_WORD && node->content && ft_strchr(node->content,
			'$') && !is_squoted(node, lex))
			node = expand_all(node, ult);
		node = node->next;
	}
	return (lex);
}
