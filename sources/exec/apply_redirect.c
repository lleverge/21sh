/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:01:05 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/15 19:50:34 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>
#include <errno.h>
#include <stdio.h>

void			set_fd_pipe(t_process *proc_1, t_process *proc_2)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_putendl_fd("21sh: pipe error", 2);
		exit(1);
	}
	proc_1->fd[1] = fd[1];
	proc_2->fd[0] = fd[0];
}

t_job			*apply_redirect(t_job *job_li, t_ult *ult)
{
	t_process 		*tmp;

	tmp = job_li->proc;
	while (tmp)
	{
		if (!main_redirection_checker(tmp, ult))
		{
			destroy_proc_list(job_li->proc);
			job_li->proc = NULL;
			break ;
		}
			tmp = tmp->next;
	}
	return (job_li);
}

void		job_launch(t_job *job_li, t_ult *ult)
{
	char		**cmd_tab;
	t_job		*tmp_job;
	t_process	*tmp_proc;
	int			fd[2];

	cmd_tab = NULL;
	tmp_job = job_li;
	errno = 0;
	while (tmp_job)
	{
		tmp_job = apply_redirect(tmp_job, ult);
		tmp_proc = tmp_job->proc;
		while (tmp_proc)
		{
			cmd_tab = ft_whitespace(tmp_proc->cmd);
			if (tmp_proc->next)
			{
				pipe(fd);
				tmp_proc->fd[1] = fd[1];
			}
			ult->ret = seek_and_exec(ult, tmp_proc, cmd_tab, fd);
			if (tmp_proc->next)
				tmp_proc->next->fd[0] = fd[0];
			free_tab(cmd_tab);
			tmp_proc = tmp_proc->next;
		}
		wait_for_procs(tmp_job->proc);
		tmp_job = tmp_job->next;
	}
	free(ult->term);
	ult->term = init_term();
}
