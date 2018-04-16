/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:15:14 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/16 19:48:14 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"
#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static int		is_quoted_char(char *base_string, int index, char c)
{
	int			flag;

	flag = 1;
	while (index >= 0)
	{
		if (base_string[index] == c)
			flag++;
		index--;
	}
	return (flag % 2 ? 1 : 0);
}

t_lexer			*new_word_init(char **raw_buff, t_token_id t_id)
{
	char	delim;
	char	*tmp;
	int		end;
	t_lexer	*new;

	end = ft_strlen(*raw_buff) - 1;
	tmp = *raw_buff;
	if (t_id == DQUOTE)
		delim = '"';
	else
		delim = '\'';
	if (end > 0)
		end--;
	while (end > 0 && tmp[end] != delim)
	{
		if (is_quoted_char(*raw_buff, end, delim))
			break ;
		end--;
	}
	tmp = ft_strsub(*raw_buff, 0, end);
	new = create_lexer_node(tmp);
	tmp ? ft_strdel(&tmp) : NULL;
	new->token_id = TOK_WORD;
	return (new);
}

t_lexer			*end_prompted_extract(char **raw_buff, t_token_id t_id)
{
	char	delim;
	char	*tmp;
	int		end;
	t_lexer	*new;

	end = ft_strlen(*raw_buff) - 1;
	tmp = *raw_buff;
	if (t_id == DQUOTE)
		delim = '"';
	else
		delim = '\'';
	if (end > 0)
		end--;
	while (end > 0 && tmp[end] != delim)
	{
		if (is_quoted_char(*raw_buff, end, delim))
			break ;
		end--;
	}
	new = init_lexer(&tmp[end]);
	return (new);
}
