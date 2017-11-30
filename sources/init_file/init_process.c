/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:18:14 by lleverge          #+#    #+#             */
/*   Updated: 2017/11/28 16:07:52 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

t_process			*stock_proc(t_process *proc, int i)
{
	static t_process *tmp = NULL;

	if (i == 0)
		tmp = proc;
	return (tmp);
}

void				proc_pushb(t_process **head, t_process *new)
{
	t_process		*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_process			*create_proc_node(t_process *proc, char *cmd)
{
	if (!(proc = (t_process *)malloc(sizeof(t_process))))
	{
		ft_putendl_fd("error: process struct malloc failed", 2);
		exit(-1);
	}
	proc->cmd = ft_strdup(cmd);
	proc->token_id = -1;
	proc->fd[0] = -1;
	proc->fd[1] = -1;
	proc->fd[2] = -1;
	proc->pid = -1;
	proc->done = -1;
	proc->fd_to_close = NULL;
	proc->next = NULL;
	return (proc);
}

t_process			*process_list(t_process *proc, char *cmd)
{
	t_process		*new;

	new = NULL;
	new = create_proc_node(new, cmd);
	if (new)
		proc_pushb(&proc, new);
	return (proc);
}
