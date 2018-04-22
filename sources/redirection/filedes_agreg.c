/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedes_agreg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 19:39:38 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/22 19:57:08 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int			which_fd_agreg(char *cmd)
{
	char			*sub_cmd;
	int				i;
	int				j;
	int				fd;

	sub_cmd = NULL;
	sub_cmd = ft_strsub(sub_cmd, 0, (ft_strchr(sub_cmd, '>') - sub_cmd));
	i = ft_strlen(sub_cmd) - 1;
	j = i;
	while (j >= 0 && !ft_isdigit(cmd[j]))
		j--;
	if (j == -1)
		return (1);
	if (ft_isdigit(sub_cmd[i]))
	{
		while (i > 0 && ft_isdigit(sub_cmd[i]))
			i--;
	}
	fd = ft_atoi(&sub_cmd[i]);
	sub_cmd ? ft_strdel(&sub_cmd) : NULL;
	if (fd == 0 || fd == 1 || fd == 2)
		return (fd);
	return (-1);
}

t_process			*close_fd(t_process *proc)
{
	int				fd;
	t_close			*new;
	t_close			*tmp;

	tmp = NULL;
	fd = which_fd_agreg(proc->cmd);
	new = close_init(fd);
	tmp = proc->fd_to_close;
	if (!tmp)
		proc->fd_to_close = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (proc);
}

int					detect_close(char *cmd)
{
	char			*tmp;

	tmp = ft_strchr(cmd, '>');
	tmp += 2;
	if (!(*tmp))
	{
		ft_putendl_fd("parse error near '&'", 2);
		return (-1);
	}
	if (*tmp == '-')
		return (95);
	return (0);
}

int					get_target_fd(char *cmd)
{
	char			*sub_cmd;
	char			*word_to_atoi;
	int				fd;

	sub_cmd = ft_strchr(cmd, '&') + 1;
	word_to_atoi = get_word(sub_cmd);
	fd = ft_atoi(word_to_atoi);
	word_to_atoi ? ft_strdel(&word_to_atoi) : NULL;
	return (fd);
}

t_process			*agreg_output(t_process *proc)
{
	char			*sub_str;
	int				fd;

	sub_str = ft_strchr(proc->cmd, '>') + 1;
	if (check_error_redir(sub_str, ">") == -1)
		return (NULL);
	proc = standard_fd(proc);
	if (detect_close(proc->cmd) == 95)
		proc = close_fd(proc);
	else
	{
		fd = which_fd_agreg(proc->cmd);
		if (fd == -1)
			return (cmd_epur_agreg(proc));
		if (get_target_fd(proc->cmd) < 0 || get_target_fd(proc->cmd) > 2)
		{
			ft_putendl_fd("21sh : Bad file descriptor.", 2);
			proc = cmd_epur_agreg(proc);
			return (NULL);
		}
		proc->fd[fd] = get_target_fd(proc->cmd);
	}
	return (cmd_epur_agreg(proc));
}
