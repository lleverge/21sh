/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:21:48 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/29 13:15:32 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"
#include "../../includes/cmd_edit.h"

void		heredoc_write(int fd, char *delim, t_ult *ult)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line ? ft_strdel(&line) : 0;
		line = termcaps_heredoc(ult);
		if (!line || !ft_strcmp(line, delim))
			break ;
		if (write(fd, line, ft_strlen(line)) == -1)
			ft_putendl_fd("21sh: write error", 2);
	}
	line ? ft_strdel(&line) : 0;
}

static int	get_epur_size_heredoc(char *cmd)
{
	int		to_epur;
	char	*tmp;
	int		start;

	to_epur = 0;
	start = ft_strchr(cmd, '<') - cmd;
	tmp = &cmd[start];
	while (tmp[to_epur] && tmp[to_epur] == '<')
		to_epur++;
	if (tmp[to_epur] && (tmp[to_epur] == '\'' || tmp[to_epur] == '\"'))
		quote_extracter(tmp, &to_epur);
	else
	{
		while (tmp[to_epur] && (tmp[to_epur] < 33 || tmp[to_epur] > 126))
			to_epur++;
		if (tmp[to_epur] && (tmp[to_epur] == '\'' || tmp[to_epur] == '\"'))
			quote_extracter(tmp, &to_epur);
		else
			while (is_validchar(tmp, to_epur))
				to_epur++;
	}
	return (to_epur);
}

t_process	*clean_exit_heredoc(int fd[2], char **delim)
{
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
	{
		ft_putendl_fd("21sh: close error", 2);
		return (NULL);
	}
	ft_strdel(delim);
	return (NULL);
}

t_process	*cmd_epur_heredoc(t_process *proc)
{
	char	*sub_str;
	int		start_pos;
	int		w_length;
	char	*new_cmd;

	start_pos = ft_strchr(proc->cmd, '<') - proc->cmd;
	w_length = get_epur_size_heredoc(proc->cmd);
	sub_str = ft_strsub(proc->cmd, start_pos, w_length);
	new_cmd = ft_extracter(proc->cmd, sub_str);
	ft_strdel(&proc->cmd);
	proc->cmd = new_cmd;
	ft_strdel(&sub_str);
	return (proc);
}
