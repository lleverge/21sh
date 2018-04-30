/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 17:09:10 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/30 16:19:52 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

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
	if (start_pos >= 1)
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

static int			get_start_pos_app(char *cmd)
{
	int		start;

	start = 0;
	while (cmd[start] != '>')
		start++;
	if (start >= 1 && ft_isdigit(cmd[start - 1]))
	{
		while (start >= 1 && ft_isdigit(cmd[start - 1]))
			start--;
	}
	if (start >= 1 && ft_isalpha(cmd[start - 1]))
		start = ft_strchr(cmd, '>') - cmd;
	return (start);
}

static int			which_fd_ap(char *cmd)
{
	char			*sub_cmd;
	char			*to_atoi;
	int				fd;

	sub_cmd = &cmd[get_start_pos_app(cmd)];
	if (*sub_cmd == '>')
		return (1);
	if (*sub_cmd == '0' && sub_cmd[1] == '>')
		return (0);
	to_atoi = NULL;
	to_atoi = fd_to_atoi(sub_cmd);
	fd = ft_atoi(to_atoi);
	to_atoi ? ft_strdel(&to_atoi) : NULL;
	return (fd);
}

t_process			*append_redirect(t_process *proc)
{
	char			*sub_str;
	char			*file_name;
	int				fd;

	sub_str = ft_strchr(proc->cmd, '>') + 2;
	if (check_error_redir(sub_str, ">>") == -1)
		return (NULL);
	file_name = get_word(sub_str);
	if ((fd = open(file_name, O_APPEND | O_CREAT | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		get_open_err(file_name, W_OK);
		ft_strdel(&file_name);
		return (NULL);
	}
	if (which_fd_ap(proc->cmd) == 1 || which_fd_ap(proc->cmd) == 2)
		proc->fd[which_fd_ap(proc->cmd)] = fd;
	else
		proc = standard_fd(proc);
	proc = cmd_epur_append(proc);
	ft_strdel(&file_name);
	return (proc);
}
