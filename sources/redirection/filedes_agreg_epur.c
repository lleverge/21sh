/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedes_agreg_epur.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 18:03:12 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/22 20:58:41 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int					get_start_pos_agreg(char *cmd)
{
	int		start;

	start = 0;
	while (cmd[start] && cmd[start + 1] && cmd[start] != '>' && cmd[start + 1]
	!= '&')
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

int					get_epur_size_agreg(char *cmd)
{
	int				to_epur;
	char			*tmp;
	int				start;

	to_epur = 0;
	start = get_start_pos_agreg(cmd);
	tmp = &cmd[start];
	while (tmp[to_epur] && tmp[to_epur + 1] && tmp[to_epur] != '>'
		&& tmp[to_epur + 1] != '&')
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

t_process			*cmd_epur_agreg(t_process *proc)
{
	char			*sub_str;
	int				start_pos;
	int				w_length;
	char			*new_cmd;

	start_pos = ft_strchr(proc->cmd, '>') - proc->cmd;
	if (start_pos > 1)
		if (ft_isdigit(proc->cmd[start_pos - 1]))
			start_pos = get_start_pos_agreg(proc->cmd);
	w_length = get_epur_size_agreg(proc->cmd);
	sub_str = ft_strsub(proc->cmd, start_pos, w_length);
	new_cmd = ft_extracter(proc->cmd, sub_str);
	ft_strdel(&proc->cmd);
	proc->cmd = new_cmd;
	ft_strdel(&sub_str);
	return (proc);
}
