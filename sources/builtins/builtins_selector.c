/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_selector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:37:50 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/17 22:13:22 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/builtins.h"
#include "../../includes/cmd_edit.h"

int			check_for_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (2);
	else if (!ft_strcmp(cmd, "setenv"))
		return (3);
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (4);
	else if (!ft_strcmp(cmd, "echo"))
		return (5);
	else if (!ft_strcmp(cmd, "exit"))
		return (6);
	else
		return (0);
}

static int	search_for_builtins_2(t_ult *ult, char **arg)
{
	if (!ft_strcmp(arg[0], "env"))
		ult->ret = env_builtin(ult, arg);
	else if (!ft_strcmp(arg[0], "cd"))
		ult->ret = ft_cd(&ult->env, arg);
	else if (!ft_strcmp(arg[0], "unsetenv"))
		ult->env = split_to_unset(ult);
	return (ult->ret);
}

int			search_for_builtins(t_ult *ult, t_process *proc)
{
	char	**arg;

	arg = NULL;
	arg = cmd_format(proc->cmd);
	if (!arg)
		return (2);
	if (!ft_strlen(arg[0]))
		ult->ret = 2;
	else if (!ft_strcmp(arg[0], "exit"))
	{
		if (clean_exit(arg, ult->ret) != -1)
		{
			reset_term(ult->term);
			exit(clean_exit(arg, ult->ret));
		}
		ult->ret = -1;
	}
	else if (!ft_strcmp(arg[0], "echo"))
		ult->ret = ft_echo(&arg[1]);
	else if (!ft_strcmp(arg[0], "setenv"))
		ult->env = split_to_set(ult);
	ult->ret = search_for_builtins_2(ult, arg);
	free_tab(arg);
	return (ult->ret);
}
