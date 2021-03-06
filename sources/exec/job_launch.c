/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 19:28:46 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/27 14:35:31 by vfrolich         ###   ########.fr       */
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

static int		to_close(t_close *close_fd, int fd)
{
	t_close		*tmp;

	tmp = close_fd;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void			proc_launch(t_process *proc, t_ult *ult, int fd[2])
{
	t_process	*tmp_proc;
	char		**cmd_tab;

	cmd_tab = NULL;
	tmp_proc = proc;
	while (tmp_proc)
	{
		cmd_tab = cmd_format(tmp_proc->cmd);
		if (tmp_proc->next)
		{
			pipe(fd);
			if (tmp_proc->fd[1] == 1 && !to_close(tmp_proc->fd_to_close, 1))
				tmp_proc->fd[1] = fd[1];
			else
				close(fd[1]);
		}
		if (count_process(proc) > 1)
			fork_setup(tmp_proc, ult, fd);
		else
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
