/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:16:39 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/08 18:06:27 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <shell.h>

// void		job_launch(t_job *job_li, t_ult *ult)
// {
// 	char		**cmd_tab;
// 	t_job		*tmp_job;
// 	t_process	*tmp_proc;
// 	int			fd[2];

// 	cmd_tab = NULL;
// 	tmp_job = job_li;
// 	while (tmp_job)
// 	{
// 		tmp_job = apply_redirect(tmp_job, ult);
// 		tmp_proc = tmp_job->proc;
// 		while (tmp_proc)
// 		{
// 			cmd_tab = ft_whitespace(tmp_proc->cmd);
// 			if (tmp_proc->next)
// 			{
// 				if (pipe(fd) == -1)
// 				{	
// 					ft_putendl_fd("21sh: pipe error", 2);
// 					exit(1);
// 				}
// 				tmp_proc->fd[1] = fd[1];
// 			}
// 			if (tmp_proc->next)
// 				tmp_proc->next->fd[0] = fd[0];
// 			ult->ret = seek_and_exec(ult, tmp_proc, cmd_tab);
// 			free_tab(cmd_tab);
// 			tmp_proc = tmp_proc->next;
// 		}
// 		tmp_proc = tmp_job->proc;
// 		wait_for_all(tmp_job->proc);
// 		tmp_job = tmp_job->next;
// 	}
// }

// int			process_launch(t_process *proc, t_ult *ult)
// {
// 	int			fd[2];
// 	t_process	*tmp;
// 	char		**cmd_tab;

// 	tmp = proc;
// 	while (tmp_proc)
// 	{
// 		cmd_tab = ft_whitespace(tmp_proc->cmd);
// 		if (tmp_proc->next)
// 		{
// 			if (pipe(fd) == -1)
// 			{	
// 				ft_putendl_fd("21sh: pipe error", 2);
// 				exit(1);
// 			}
// 			tmp_proc->fd[1] = fd[1];
// 		}
// 		// set_fd_pipe(tmp_proc, tmp_proc->next);
// 		ult->ret = seek_and_exec(ult, tmp_proc, cmd_tab);
// 		if (tmp_proc->next)
// 			tmp_proc->next->fd[0] = fd[0];
// 		free_tab(cmd_tab);
// 		tmp_proc = tmp_proc->next;
// 	}
// 	wait_for_all(tmp_job->proc);
	
// }