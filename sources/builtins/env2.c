/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:48:19 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/16 18:01:53 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"
#include "../../includes/cmd_edit.h"

char			*word_array_to_str(char **args_arr)
{
	char	**tmp;
	char	*dest;

	dest = NULL;
	tmp = args_arr;
	if (**tmp == '-')
		tmp++;
	while (*tmp && ft_strchr(*tmp, '='))
		tmp++;
	if (*tmp)
	{
		dest = ft_strdup(*tmp);
		dest = ft_strjoin_free_one(&dest, " ");
		tmp++;
	}
	while (*tmp)
	{
		dest = ft_strjoin_free_one(&dest, *tmp);
		dest = ft_strjoin_free_one(&dest, " ");
		tmp++;
	}
	return (dest);
}

t_lexer			*fill_lexer_env(t_ult *ult, char *cmd)
{
	t_lexer		*lexlist;

	lexlist = init_lexer(cmd);
	if (!(lexlist = quote_tok(lexlist, ult)))
		return (NULL);
	lexlist = merge_token(lexlist);
	lexlist = prompt_pipe(lexlist, ult);
	lexlist = quote_tok(lexlist, ult);
	if (!(lexlist = quote_tok(lexlist, ult)))
		return (NULL);
	lexlist = merge_token(lexlist);
	if (parse_error(lexlist, ult->fd[2]) == -1)
		return (NULL);
	return (lexlist);
}

static void		clean_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putchar('\n');
}

static void		job_launch_bis(char **cmd_tab, t_job *tmp_job,
							t_ult *ult, int *fd)
{
	cmd_tab = ft_whitespace(tmp_job->proc->cmd);
	if (tmp_job->proc->next)
	{
		pipe(fd);
		tmp_job->proc->fd[1] = fd[1];
	}
	ult->ret = seek_and_exec(ult, tmp_job->proc, cmd_tab, fd);
	if (tmp_job->proc->next)
		tmp_job->proc->next->fd[0] = fd[0];
	cmd_tab ? free_tab(cmd_tab) : NULL;
	tmp_job->proc = tmp_job->proc->next;
}

void			job_launch_env(t_job *job_li, t_ult *ult)
{
	char		**cmd_tab;
	t_job		*tmp_job;
	t_process	*tmp_proc;
	int			fd[2];

	cmd_tab = NULL;
	tmp_job = job_li;
	signal(SIGINT, &clean_sigint);
	while (tmp_job)
	{
		tmp_job = apply_redirect(tmp_job, ult);
		tmp_proc = tmp_job->proc;
		while (tmp_proc)
			job_launch_bis(cmd_tab, tmp_job, ult, fd);
		wait_for_procs(tmp_job->proc);
		tmp_job = tmp_job->next;
	}
}
