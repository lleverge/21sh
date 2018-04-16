/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:18:14 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/16 15:00:47 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

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

t_close				*close_init(int fd)
{
	t_close			*new;
	t_ult			*ult;

	new = NULL;
	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!(new = (t_close *)malloc(sizeof(t_close))))
	{
		ft_putendl_fd("error: process struct malloc failed", 2);
		exit_term(ult->term);
		exit(3);
	}
	new->fd = fd;
	new->next = NULL;
	return (new);
}

t_process			*create_proc_node(char *cmd, int token_id)
{
	t_process	*proc;
	t_ult		*ult;

	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!(proc = (t_process *)malloc(sizeof(t_process))))
	{
		ft_putendl_fd("error: process struct malloc failed", 2);
		exit_term(ult->term);
		exit(3);
	}
	proc->cmd = ft_strdup(cmd);
	proc->token_id = token_id;
	proc->fd[0] = -1;
	proc->fd[1] = -1;
	proc->fd[2] = -1;
	proc->pid = -1;
	proc->done = -1;
	proc->fd_to_close = NULL;
	proc->next = NULL;
	return (proc);
}
