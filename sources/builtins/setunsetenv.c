/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setunsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:02:37 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/16 18:12:56 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"
#include "../../includes/builtins.h"

t_env		*split_to_set(t_ult *ult)
{
	char	**splited_cmd;

	splited_cmd = NULL;
	splited_cmd = ft_whitespace(ult->cmd);
	ult->env = add_all_env(ult, splited_cmd);
	free_tab(splited_cmd);
	return (ult->env);
}

void		unset_error(char *cmd)
{
	ft_putstr_fd("21sh: unset: '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("': not a valid indentifier", 2);
}
