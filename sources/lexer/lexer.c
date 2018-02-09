                   /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2018/01/27 17:43:35 by vfrolich         ###   ########.fr       */
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

int			start_prog(t_lexer *lex, t_ult *ult)
{
	t_job		*job;
	t_process	*proc;
	char		*cmd;
	char		*tmp;
	char		**tmp2;

	job = NULL;
	proc = NULL;
	cmd = ft_strdup("");
	while (lex)
	{
		tmp = ft_strdup(lex->content);
		cmd = ft_strjoin_free(&cmd, &tmp);
		if (lex->token_id == PIPE)
		{
			proc_pushb(&proc, create_proc_node(cmd, lex->token_id));
			ft_strdel(&cmd);
			cmd = ft_strdup("");
		}
		else if (lex->token_id == SEPARATOR || !lex->next)
		{
			proc_pushb(&proc, create_proc_node(cmd, SEPARATOR));
			job_pushb(&job, create_job_node(proc));
			ft_strdel(&cmd);
			cmd = ft_strdup("");
			proc = NULL;
		}
		lex = lex->next;
	}
	tmp2 = ft_whitespace(ult->cmd);
	ult->ret = seek_and_exec(ult, job, tmp2);
	free_tab(tmp2);
	destroy_job_list(job);
	ft_strdel(&cmd);
	return (ult->ret);
}

/*int			start_prog(t_ult *ult, char **cmd)
{
	int		i;
	t_job	*job_li;
	t_job	*new;
	char	**cmd_tab;

	i = 0;
	job_li = NULL;
	cmd_tab = ft_strsplit_ws(cmd[0]);
	while (cmd[i])
	{
		new = create_job_node(cmd[i]);
		job_pushb(&job_li, new);
		job_li->proc = main_redirection_checker(job_li->proc, ult);
		i++;
	}
	if (job_li->proc)
		ult->ret = seek_and_exec(ult, job_li, cmd_tab);
	free_tab(cmd_tab);
	destroy_job_list(job_li);
	return (0);
	}*/
