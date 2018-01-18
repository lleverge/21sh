/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:36:31 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/18 21:48:04 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>
#include <lexer.h>

char 			*prompt_until_quote(t_ult *ult, t_token_id tok_id)
{
	char		delim;
	char		*cmd;
	char		*tmp;
	
	cmd = NULL;
	if (tok_id == DQUOTE)
		delim = '"';
	else 
		delim = '\'';
	cmd = termcaps_heredoc(ult);
	tmp = cmd;
	if (!cmd)
		return (NULL);
	while (!ft_strchr(cmd , delim))
	{
		if (!(cmd = termcaps_heredoc(ult)))
		{
			ft_strdel(&tmp);
			return (NULL);
		}
		cmd = ft_strjoin_free(&tmp, &cmd);
		tmp = cmd;
	}
	cmd[ft_strlen(cmd) - 1] == '\n' ? cmd[ft_strlen(cmd) - 1] = '\0' : 0;
	return (cmd);
}

int		check_closed_quote(t_lexer **list)
{
		t_lexer 	*tmp;
		t_token_id 	tok_value;

		tmp = *list;
		tok_value = tmp->token_id;
		tmp = tmp->next;
		while (tmp)
		{
			if (tmp->token_id == tok_value)
			{
				*list = tmp;
				return (1);
			}
			tmp = tmp->next;
		}
		return (0);
}


t_lexer *quote_tok(t_lexer *lexlist, t_ult *ult)
{
	t_lexer	*tmp;
	char	*closed_quote;
	t_lexer	*lex_end;

	tmp = lexlist;
	lex_end = NULL;
	while (tmp)
	{
		if (tmp->token_id == QUOTE || tmp->token_id == DQUOTE)
		{
			if (!check_closed_quote(&tmp))
			{
				if (!(closed_quote = prompt_until_quote(ult, tmp->token_id)))
					return (NULL);
				lex_end = init_lexer(closed_quote);
				ft_strdel(&closed_quote);
				lex_push(lex_end, &lexlist);
				return (lexlist);
			}
		}
			tmp = tmp->next;
	}
	return (lexlist);
}
