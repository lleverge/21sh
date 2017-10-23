/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:46:25 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/23 16:30:11 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void				job_pushb(t_job **head, t_job *new)
{
	t_job		*tmp;

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

t_job				*create_job_node(char *cmd, char *cmdnosp)
{
	t_job		*job;

	if (!(job = (t_job *)malloc(sizeof(t_job))))
	{
		ft_putendl_fd("error: job struct malloc failed", 2);
		exit(-1);
	}
	job->cmd = ft_strdup(cmd);
	job->cmdnosp = ft_strdup(cmdnosp);
	job->linker = 0;
	job->pgid = 0;
	job->proc = NULL;
	job->next = NULL;
	return (job);
}

t_job				*job_list(t_job *job, char *cmd, char *cmdnosp)
{
	t_job		*new;

	new = create_job_node(cmd, cmdnosp);
	if (new)
		job_pushb(&job, new);
	return (job);
}
