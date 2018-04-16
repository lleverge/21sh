/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:46:25 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/16 14:59:52 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

void				job_pushb(t_job **head, t_job *new)
{
	t_job		*tmp;

	if (!(*head))
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_job				*create_job_node(t_process *proc)
{
	t_job		*job;
	t_ult		*ult;

	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!(job = (t_job *)malloc(sizeof(t_job))))
	{
		ft_putendl_fd("error: job struct malloc failed", 2);
		exit_term(ult->term);
		exit(-1);
	}
	job->linker = 0;
	job->pgid = 0;
	job->proc = proc;
	job->next = NULL;
	return (job);
}
