/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 19:01:05 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/22 16:22:32 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"
#include "../../includes/shell.h"
#include "../../includes/lexer.h"

static void		close_push(t_close *elem, t_close **closelist)
{
	t_close		*tmp;

	if (!*closelist)
		*closelist = elem;
	else
	{
		tmp = *closelist;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
}

t_job			*apply_redirect(t_job *job_li, t_ult *ult)
{
	t_process	*tmp;
	t_close		*close_fd;

	tmp = job_li->proc;
	while (tmp)
	{
		if (!main_redirection_checker(tmp, ult))
		{
			close_fd = close_init(1);
			close_push(close_fd, &tmp->fd_to_close);
		}
		tmp = tmp->next;
	}
	return (job_li);
}
