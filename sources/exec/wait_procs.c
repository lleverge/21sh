/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_procs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 16:14:39 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/15 14:18:23 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

int		count_process(t_process *proc)
{
	int 		count;
	t_process 	*tmp;

	count = 0;
	tmp = proc;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

t_process		*proc_from_pid(int pid, t_process *proclist)
{
	t_process 	*tmp;

	tmp = proclist;
	while (tmp)
	{
		if (tmp->pid == pid)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void			udpate_status(t_process *proc, pid_t pid, int status)
{
	t_process	*tmp;

	if (!(tmp = proc_from_pid(pid, proc)))
		return ;
	tmp->done = status;
}

void			wait_for_procs(t_process *procs)
{
	int			count;
	pid_t		pid;
	int			tmp_status;
	t_process	*proc;

	pid = 0;
	proc = procs;
	count = count_process(procs);
	while (count > 0)
	{
		pid = waitpid(0, &tmp_status, WUNTRACED);
		if (pid == -1)
		{
			break ;
		}
		udpate_status(procs, pid, tmp_status);
		count--;
	}
}
