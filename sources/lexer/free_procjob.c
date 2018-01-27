/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_procjob.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 20:27:03 by lleverge          #+#    #+#             */
/*   Updated: 2018/01/27 16:16:38 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void	destroy_fd_list(t_process *proc)
{
	t_close	*tmp;

	tmp = NULL;
	while (proc->fd_to_close)
	{
		tmp = proc->fd_to_close->next;
		free(proc->fd_to_close);
		proc->fd_to_close = tmp;
	}
}

void	destroy_proc_one(t_process *proc)
{
	ft_strdel(&proc->cmd);
	destroy_fd_list(proc);
	free(proc);
	proc = NULL;
}

void	destroy_proc_list(t_process *proc_list)
{
	t_process	*tmp;

	while (proc_list)
	{
		tmp = proc_list->next;
		destroy_proc_one(proc_list);
		proc_list = tmp;
	}
}

void	destroy_job_one(t_job *job)
{
	destroy_proc_list(job->proc);
	free(job);
	job = NULL;
}

void	destroy_job_list(t_job *job_list)
{
	t_job	*tmp;

	while (job_list)
	{
		tmp = job_list->next;
		destroy_job_one(job_list);
		job_list = tmp;
	}
}
