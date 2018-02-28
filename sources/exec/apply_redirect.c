/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:01:05 by vfrolich          #+#    #+#             */
/*   Updated: 2018/02/28 18:28:53 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

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
	t_job 		*tmp;
	t_process 	*tmp2;
	t_process	*proc_list;

	tmp = job_li;
	while (tmp)
	{
		tmp2 = tmp->proc;
		proc_list = tmp2;
		while (tmp2)
		{
			if (!main_redirection_checker(tmp->proc, ult))
			{
				destroy_proc_list(proc_list);
				tmp->proc = NULL;
				proc_list = NULL;
				break ;
			}
			tmp2 = tmp2->next;
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

	cmd_tab = NULL;
	tmp_job = job_li;
	while (tmp_job)
	{
		tmp_proc = tmp_job->proc;
		while (tmp_proc)
		{
			cmd_tab = ft_whitespace(tmp_proc->cmd);
			if (tmp_proc->next)
				set_fd_pipe(tmp_proc, tmp_proc->next);
			ult->ret = seek_and_exec(ult, tmp_proc, cmd_tab);
			free_tab(cmd_tab);
			tmp_proc = tmp_proc->next;
		}
		tmp_job = tmp_job->next;
	}
}

// base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g'