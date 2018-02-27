/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:01:05 by vfrolich          #+#    #+#             */
/*   Updated: 2018/02/27 18:19:57 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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
