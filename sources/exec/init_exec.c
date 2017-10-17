/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:27:53 by lleverge          #+#    #+#             */
/*   Updated: 2017/04/06 19:34:24 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

void		free_exec(t_exec *exec)
{
	exec->pid = 0;
	exec->fd_write = 0;
	exec->fd_read = 0;
	free(exec);
	exec = NULL;
}

t_exec		*create_exec(void)
{
	t_exec	*new;

	if (!(new = (t_exec *)malloc(sizeof(t_exec))))
	{
		ft_putendl_fd("21sh: error: exec malloc failed", 2);
		exit(-1);
	}
	new->pid = 0;
	new->fd_write = 1;
	new->fd_read = 0;
	new->stdin_cp = 0;
	new->stdout_cp = 0;
	return (new);
}
