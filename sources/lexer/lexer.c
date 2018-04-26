/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/26 16:28:34 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

t_lexer			*fill_lexer_2(t_lexer **oldlex)
{
	t_lexer		*dup;

	dup = NULL;
	dup = lexdup(*oldlex);
	dup = merge_token(dup);
	if (parse_error(dup) == -1)
	{
		free_lexer(&dup);
		free_lexer(oldlex);
		return (NULL);
	}
	free_lexer(&dup);
	return (*oldlex);
}

t_lexer			*fill_lexer(t_ult *ult)
{
	t_lexer		*lexlist;

	lexlist = init_lexer(ult->cmd);
	if (!(lexlist = quote_tok(lexlist, ult)))
		return (NULL);
	lexlist = merge_token(lexlist);
	lexlist = prompt_pipe(lexlist, ult);
	lexlist = quote_tok(lexlist, ult);
	if (!(lexlist = quote_tok(lexlist, ult)))
		return (NULL);
	lexlist = fill_lexer_2(&lexlist);
	ult->cmd ? ft_strdel(&ult->cmd) : NULL;
	ult->cmd = lexer_to_str(lexlist);
	return (lexlist);
}

static void		pipe_token(t_lexer *lex, t_process **proc, char **cmd)
{
	proc_pushb(proc, create_proc_node(*cmd, lex->token_id));
	ft_strdel(cmd);
	*cmd = ft_strdup("");
}

static void		separator_token(char **cmd, t_job **job, t_process **proc)
{
	proc_pushb(proc, create_proc_node(*cmd, SEPARATOR));
	job_pushb(job, create_job_node(*proc));
	ft_strdel(cmd);
	*cmd = ft_strdup("");
	*proc = NULL;
}

t_job			*set_jobs(t_lexer *lex)
{
	t_job		*job;
	t_process	*proc;
	char		*cmd;
	char		*tmp;

	job = NULL;
	proc = NULL;
	cmd = ft_strdup("");
	while (lex)
	{
		if (!fine_token(lex->token_id) && (lex->token_id != DQUOTE
		|| lex->token_id != QUOTE))
		{
			tmp = ft_strdup(lex->content);
			cmd = ft_strjoin_free(&cmd, &tmp);
		}
		if (lex->token_id == PIPE)
			pipe_token(lex, &proc, &cmd);
		else if (lex->token_id == SEPARATOR || !lex->next)
			separator_token(&cmd, &job, &proc);
		lex = lex->next;
	}
	cmd ? ft_strdel(&cmd) : NULL;
	return (job);
}
