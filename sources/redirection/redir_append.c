/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 17:09:10 by vfrolich          #+#    #+#             */
/*   Updated: 2017/10/24 15:48:34 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

static int			get_epur_size_append(char *cmd)
{
	int				to_epur;
	char			*tmp;
	int				start;

	to_epur = 0;
	start = get_start_pos(cmd);
	tmp = &cmd[start];
	while (tmp[to_epur] && tmp[to_epur] != '>')
		to_epur++;
	if (tmp[to_epur + 1])
		to_epur++;
	if (tmp[to_epur + 1])
		to_epur++;
	while (tmp[to_epur] && (tmp[to_epur] < 33 || tmp[to_epur] > 126))
		to_epur++;
	while (tmp[to_epur] && (tmp[to_epur] >= 33 && tmp[to_epur] <= 126))
		to_epur++;
	return (to_epur);
}

static t_process	*cmd_epur_append(t_process *proc)
{
	char			*sub_str;
	int				start_pos;
	int				w_length;
	char			*new_cmd;

	start_pos = ft_strchr(proc->cmd, '>') - proc->cmd;
	if (start_pos > 1)
		if (ft_isdigit(proc->cmd[start_pos - 1]))
			start_pos = get_start_pos(proc->cmd);
	w_length = get_epur_size_append(proc->cmd) + 1;
	sub_str = ft_strsub(proc->cmd, start_pos, w_length);
	new_cmd = ft_extracter(proc->cmd, sub_str);
	ft_strdel(&proc->cmd);
	proc->cmd = new_cmd;
	ft_strdel(&sub_str);
	return (proc);
}

t_process			*append_redirect(t_process *proc)
{
	char			*sub_str;
	char			*file_name;
	int				fd;

	sub_str = ft_strchr(proc->cmd, '>') + 2;
	if (check_error_redir(sub_str, ">>") == -1)
	{
		free_process_one(proc);
		return (NULL);
	}
	file_name = get_word(sub_str);
	if ((fd = open(file_name, O_APPEND | O_CREAT | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		get_open_err(file_name, W_OK);
		ft_strdel(&file_name);
		free_process_one(proc);
		return (NULL);
	}
	proc->fd[which_fd(proc->cmd)] = fd;
	proc = standard_fd(proc);
	proc = cmd_epur_append(proc);
	ft_strdel(&file_name);
	return (proc);
}
