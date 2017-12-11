/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_selector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:37:50 by vfrolich          #+#    #+#             */
/*   Updated: 2017/12/11 23:03:19 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <builtins.h>
#include <cmd_edit.h>

int		search_for_builtins_2(t_ult *ult, char **arg)
{
	if (!ft_strcmp(arg[0], "env"))
		print_list(ult->env);
	else if (!ft_strcmp(arg[0], "cd"))
		ult->ret = ft_cd(ult->env, arg);
	else if (!ft_strcmp(arg[0], "unsetenv"))
		ult->env = split_to_unset(ult);
	return (ult->ret);
}

int		search_for_builtins(t_ult *ult)
{
	char	**arg;

	arg = NULL;
	arg = ft_whitespace(ult->cmd);
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
	else if (!ft_strcmp(arg[0], "setenv") || !ft_strcmp(arg[0], "export"))
		ult->env = split_to_set(ult);
	ult->ret = search_for_builtins_2(ult, arg);
	free_tab(arg);
	return (ult->ret);
}
