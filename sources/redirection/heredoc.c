/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 15:52:23 by vfrolich          #+#    #+#             */
/*   Updated: 2017/10/23 16:09:47 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/shell.h"
// #include "../../includes/lexer.h"

#include <shell.h>
#include <lexer.h>

// static t_process		*create_proc_node_one(t_process *proc, char *cmd)
// {
// 	if (!(proc = (t_process *)malloc(sizeof(t_process))))
// 	{
// 		ft_putendl_fd("error: process struct malloc failed", 2);
// 		exit(-1);
// 	}
// 	proc->cmd = ft_strdup(cmd);
// 	proc->token_id = -1;
// 	proc->fd[0] = -1;
// 	proc->fd[1] = -1;
// 	proc->fd[2] = -1;
// 	proc->pid = -1;
// 	proc->done = -1;
// 	proc->next = NULL;
// 	return (proc);
// }

// int						check_err_heredoc(t_process *proc)
// {
// 	char			*sub_cmd;

// 	sub_cmd = ft_strchr(proc->cmd, '<');
// 	if (!(sub_cmd + 2))
// 	{	
// 		ft_putendl_fd("Missing heredoc delimiter, try [command] << [delimiter]"
// 		, STDERR_FILENO);
// 		return (-1);
// 	}
// 	return (0);	
// }

// t_process				*heredoc(t_process *proc)
// {
// 	char			*sub_str;
// 	char			*file_name;
// 	int				fd;

	
// 	proc = standard_fd(proc);
// 	if (check_err_heredoc(proc) == -1)
// 	{
// 		free_process_one(proc);
// 		return (NULL);
// 	}

// 	return (proc);
// }

// static t_process *which_redir(t_process *proc)
// {
// 	char	*sub_cmd;

// 	sub_cmd = ft_strchr(proc->cmd, '>');
// 	if (sub_cmd)
// 	{
// 		if(*(sub_cmd+ 1) == '>')
// 			return (append_redirect(proc));
// 		return (simple_redirect(proc));
// 	}
// 	sub_cmd = ft_strchr(proc->cmd, '<');
// 	if (sub_cmd)
// 	{
// 		if(*(sub_cmd+ 1) == '<')
// 		{
// 			ft_putendl("too soon for heredoc");
// 			return (NULL);
// 		}
// 		return (redirect_input(proc));
// 	}
// 	return (NULL);
// }

// int			main(int argc, char **argv)
// {
// 	t_process *proc;
// 	char	buffer[1024];

// 	if (argc != 2)
// 		return (1);
// 	proc = create_proc_node_one(proc, argv[1]);
// 	proc = which_redir(proc);
// 	if (!proc)
// 		return (-1);
// 	ft_putstr("INPUT FD is -> ");
// 	ft_putnbr(proc->fd[0]);
// 	ft_putchar('\n');
// 	ft_putstr("OUTPUT FD is -> ");
// 	ft_putnbr(proc->fd[1]);
// 	ft_putchar('\n');
// 	ft_putstr("ERR FD is -> ");
// 	ft_putnbr(proc->fd[2]);
// 	ft_putchar('\n');
// 	return (0);
// }
