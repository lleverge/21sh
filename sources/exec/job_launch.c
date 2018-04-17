/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 19:28:46 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/17 22:17:27 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"
#include "../../includes/shell.h"
#include "../../includes/lexer.h"


static void		simple_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putchar('\n');
}

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

char			**cmd_format(char *cmd)
{
	t_lexer		*lexer;
	t_lexer 	*tmp;
	t_lexer		*safe;
	char		**dest;
	int			i;

	lexer = init_lexer(cmd);
	lexer = merge_token(lexer);
	if (!(dest = (char **)malloc(sizeof(char *) * (count_words(lexer) + 1))))
	{
		free_lexer(&lexer);
		return (NULL);
	}
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
	free_lexer(&lexer);
	return (dest);
}

void			proc_launch(t_process *proc, t_ult *ult, int fd[2])
{
	t_process	*tmp_proc;
	char		**cmd_tab;

	cmd_tab = NULL;
	tmp_proc = proc;
	while (tmp_proc)
	{
		if (!(cmd_tab = cmd_format(tmp_proc->cmd)))
			return ;
		if (tmp_proc->next)
		{
			pipe(fd);
			if (tmp_proc->fd[1] == 1)
				tmp_proc->fd[1] = fd[1];
			else
				close(fd[1]);
		}
		ult->ret = seek_and_exec(ult, tmp_proc, cmd_tab, fd);
		if (tmp_proc->next)
			tmp_proc->next->fd[0] = fd[0];
		cmd_tab ? free_tab(cmd_tab) : NULL;
		tmp_proc = tmp_proc->next;
	}
}

void			job_launch(t_job *job_li, t_ult *ult)
{
	t_job		*tmp_job;
	int			fd[2];

	tmp_job = job_li;
	signal(SIGINT, &simple_sigint);
	while (tmp_job)
	{
		tmp_job = apply_redirect(tmp_job, ult);
		proc_launch(tmp_job->proc, ult, fd);
		wait_for_procs(tmp_job->proc);
		tmp_job = tmp_job->next;
	}
	free(ult->term);
	ult->term = init_term();
}
