/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/11/13 16:11:14 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>
#include <cmd_edit.h>


static int		parse_error(char *cmd)
{
	int		i;

	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (ft_istoken(cmd[i]) > 0)
	{
		ft_putstr_fd("21sh: parse error near ", 2);
		ft_putchar_fd(cmd[i], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (0);
}

static int		full_parse_error(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (parse_error(cmd[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

static t_process		*create_proc_node_one(t_process *proc, char *cmd)
{
	if (!(proc = (t_process *)malloc(sizeof(t_process))))
	{
		ft_putendl_fd("error: process struct malloc failed", 2);
		exit(-1);
	}
	proc->cmd = ft_strdup(cmd);
	proc->token_id = -1;
	proc->fd[0] = -1;
	proc->fd[1] = -1;
	proc->fd[2] = -1;
	proc->pid = -1;
	proc->done = -1;
	proc->next = NULL;
	return (proc);
}

int				init_all(char **environ)
{
	t_ult		*ult;
	char		**cmd;
	t_job		*job_li;
	int			i;

	ult = NULL;
	job_li = NULL;
	ult = init_ult(ult, environ);
	while (42)
	{
		i = 0;
		get_prompt(ult->env);
		termcap(ult);
		ft_putchar('\n');
		cmd = ft_strsplit(ult->cmd, ';');
		if (cmd[i])
		{
			if (full_parse_error(cmd) == 0)
			{
				while (cmd[i])
				{
					start_prog(cmd[i], &job_li);
					i++;
				}
			}
		}
	}
	return (0);
}

int				main(int ac, char **av, char **environ)
{
	av = NULL;
	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("error: 21sh requires no arguments", 2);
		exit(-1);
	}
	init_all(environ);
	return (0);
}
