/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:01:05 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/11 19:30:00 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>
#include <lexer.h>

t_job			*apply_redirect(t_job *job_li, t_ult *ult)
{
	t_process	*tmp;

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
