/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:41:01 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/23 17:55:22 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

int					get_start_pos_input(char *cmd)
{
	int		start;

	start = 0;
	while (cmd[start] != '<')
		start++;
	if (start >= 1 && ft_isdigit(cmd[start - 1]))
	{
		while (start >= 1 && ft_isdigit(cmd[start - 1]))
			start--;
	}
	if (start >= 1 && ft_isalpha(cmd[start - 1]))
		start = ft_strchr(cmd, '<') - cmd;
	return (start);
}

int					get_epur_size_input(char *cmd)
{
	int				to_epur;
	char			*tmp;
	int				start;

	to_epur = 0;
	start = get_start_pos_input(cmd);
	tmp = &cmd[start];
	while (tmp[to_epur] && tmp[to_epur] != '<')
		to_epur++;
	if (tmp[to_epur + 1])
		to_epur++;
	if (tmp[to_epur] == '\'' || tmp[to_epur] == '\"')
		quote_extracter(tmp, &to_epur);
	else
	{
		while (tmp[to_epur] && (tmp[to_epur] < 33 || tmp[to_epur] > 126))
			to_epur++;
		while (tmp[to_epur] && (tmp[to_epur] >= 33 && tmp[to_epur] <= 126))
			to_epur++;
	}
	return (to_epur);
}

t_process			*cmd_epur_input(t_process *proc)
{
	char			*sub_str;
	int				start_pos;
	int				w_length;
	char			*new_cmd;

	start_pos = ft_strchr(proc->cmd, '<') - proc->cmd;
	if (start_pos > 1)
		if (ft_isdigit(proc->cmd[start_pos - 1]))
			start_pos = get_start_pos_input(proc->cmd);
	w_length = get_epur_size_input(proc->cmd);
	sub_str = ft_strsub(proc->cmd, start_pos, w_length);
	new_cmd = ft_extracter(proc->cmd, sub_str);
	ft_strdel(&proc->cmd);
	proc->cmd = new_cmd;
	ft_strdel(&sub_str);
	return (proc);
}

t_process			*redirect_input(t_process *proc)
{
	char			*sub_str;
	char			*file_name;
	int				fd;

	sub_str = ft_strchr(proc->cmd, '<') + 1;
	if (check_error_redir(sub_str, "<") == -1)
		return (NULL);
	file_name = get_word(sub_str);
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		get_open_err(file_name, R_OK);
		ft_strdel(&file_name);
		return (NULL);
	}
	proc->fd[0] = fd;
	proc = standard_fd(proc);
	proc = cmd_epur_input(proc);
	ft_strdel(&file_name);
	return (proc);
}
