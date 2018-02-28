/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2018/02/28 15:34:30 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

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
	lexlist = merge_token(lexlist);
	if (parse_error(lexlist, ult->fd[2]) == -1)
		return (NULL);
	return (lexlist);
}

static int	builtin_launch(t_ult *ult, t_process *proc)
{
	int 	fd[3];
	int 	ret;

	fd[0] = dup(ult->fd[0]);
	fd[1] = dup(ult->fd[1]);
	fd[2] = dup(ult->fd[2]);
	if (set_fd_exec(proc) == -1)
		return (1);
	ret = search_for_builtins(ult, proc);
	close_fd_exec(proc);
	restore_fd(fd);
	return (ret);
}

int			seek_and_exec(t_ult *ult, t_job *job, char **cmd_tab)
{
	char	**cmd_tab2;

	cmd_tab2 = cmd_tab;
	if (check_for_builtin(*cmd_tab))
		return (builtin_launch(ult, job->proc));
	if (ult->hash_table && hash_search(*cmd_tab, ult->hash_table))
		return (exe_fork(ult->env, job->proc, ult));
	if (ft_strchr(*cmd_tab, '/') && !path_access_checker(*cmd_tab))
		return (exe_fork2(ult->env, job->proc, *cmd_tab, ult));
	if (!ft_strchr(*cmd_tab, '/'))
	{
		ft_putstr_fd("21sh : command not found: ", 2);
		ft_putendl_fd(*cmd_tab, 2);
	}
	return (127);
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

int			set_jobs(t_lexer *lex)
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
		tmp = ft_strdup(lex->content);
		cmd = ft_strjoin_free(&cmd, &tmp);
		if (lex->token_id == PIPE)
			pipe_token(lex, &proc, &cmd);
		else if (lex->token_id == SEPARATOR || !lex->next)
			separator_token(&cmd, &job, &proc);
		lex = lex->next;
	}
	return (0);
}
