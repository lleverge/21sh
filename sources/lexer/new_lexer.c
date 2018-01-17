/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 20:10:09 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/17 13:32:36 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

t_lexer *word_token(char *cmd)
{
	int 	word_length;
	char	*tmp;
	t_lexer *new;

	word_length = 0;
	tmp = cmd;
	while (*tmp && !is_token_char(*tmp))
	{
		tmp++;
		word_length++;
	}
	new = NULL;
	tmp = ft_strsub(cmd, 0, word_length);
	new = create_lexer_node(tmp);
	ft_strdel(&tmp);
	new->token_id = TOK_WORD;
	return (new);
}

void	lex_push(t_lexer *new, t_lexer **lex_list)
{
	t_lexer *tmp;

	if (!(*lex_list))
	{
		*lex_list = new;
		return ;
	}
	tmp = *lex_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_lexer *single_token_init(char c)
{
	char buff[2];
	t_lexer *new;

	buff[0] = c;
	buff[1] = '\0';
	new = create_lexer_node(buff);
	new->token_id = which_token(c);
	return (new);
}

t_lexer *init_lexer(char *cmd)
{
	int index;
	t_lexer *lex_list;
	t_lexer *new;

	index = 0;
	lex_list = NULL;
	new = NULL;
	while (cmd[index])
	{
		if (is_token_char(cmd[index]))
		{
			new = single_token_init(cmd[index]);
			lex_push(new, &lex_list);
			index++;
		}
		else
		{
			new = word_token(&cmd[index]);
			lex_push(new, &lex_list);
			index += ft_strlen(new->content);
		}
	}
	return (lex_list);
}
