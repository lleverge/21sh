/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 11:55:04 by vfrolich          #+#    #+#             */
/*   Updated: 2017/12/23 13:07:14 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	ft_isbadtoken(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
}

static int is_only_number(char *sub_cmd)
{
	while (*sub_cmd)
	{
		if (!ft_isdigit(*sub_cmd))
			break ;
		sub_cmd++;
	}
	if (*sub_cmd && ft_isbadtoken(*sub_cmd))
	{
		ft_putendl("nope");
		return (-1);
	}
	return (0);
}

static int	check_deeper(char *cmd, char *to_check)
{
	char	*sub_cmd;


	if (!ft_strcmp(to_check, ">") || !ft_strcmp(to_check, "<"))
		sub_cmd = ft_strchr(cmd, *to_check) + 1;
	else
		sub_cmd = ft_strchr(cmd, *to_check) + 2;
	if (!sub_cmd)
		return (-1);
	if (is_only_number(sub_cmd) == -1)
		return (-1);
	return (0);
}

static t_process	*redir_detector(t_process *proc, t_ult *ult)
{
	if (ft_strstr(proc->cmd, ">>") && check_deeper(proc->cmd, ">>") != - 1)
		return (append_redirect(proc));
	if (ft_strstr(proc->cmd, "<<") && check_deeper(proc->cmd, "<<") != - 1)
		return (heredoc(proc, ult));
	if (ft_strstr(proc->cmd, ">&") && check_deeper(proc->cmd, ">&") != - 1)
		return (agreg_output(proc));
	if (ft_strstr(proc->cmd, "<") && check_deeper(proc->cmd, "<") != - 1)
		return (redirect_input(proc));
	if (ft_strstr(proc->cmd, ">") && check_deeper(proc->cmd, ">") != - 1)
		return (simple_redirect(proc));
	return (proc);
}

static int redir_detector_int(t_process *proc)
{
	if (ft_strstr(proc->cmd, ">>") && check_deeper(proc->cmd, ">>") != - 1)
		return (1);
	if (ft_strstr(proc->cmd, "<<") && check_deeper(proc->cmd, "<<") != - 1)
		return (2);
	if (ft_strstr(proc->cmd, ">&") && check_deeper(proc->cmd, ">&") != - 1)
		return (3);
	if (ft_strstr(proc->cmd, "<") && check_deeper(proc->cmd, "<") != - 1)
		return (4);
	if (ft_strstr(proc->cmd, ">") && check_deeper(proc->cmd, ">") != - 1)
		return (5);
	return (0);
}

t_process 	*main_redirection_checker(t_process *proc, t_ult *ult)
{	
	int 	i;

	i = 0;
	while (proc->cmd[i])
	{
		if (proc->cmd[i] == '>' || proc->cmd[i] == '<'|| proc->cmd[i] == '&')
		{
			proc = redir_detector(proc, ult);
			break ;
		}
		i++;
	}
	if (!proc)
		return (NULL);
	if (redir_detector_int(proc))
		proc = main_redirection_checker(proc, ult);
	proc = standard_fd(proc);
	return (proc);
}