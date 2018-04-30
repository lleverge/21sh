/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:18:54 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/30 18:01:00 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/builtins.h"

static int	ft_unsetenv(t_env **begin_list, char *varname)
{
	t_env	*tmp;

	tmp = *begin_list;
	if (*begin_list)
	{
		if (!(ft_strcmp((*(begin_list))->name, varname)))
		{
			tmp = *begin_list;
			*begin_list = (*(begin_list))->next;
			ft_strdel(&(tmp->name));
			ft_strdel(&(tmp->content));
			free(tmp);
			tmp = NULL;
			return (0);
		}
		else
			ft_unsetenv(&(*begin_list)->next, varname);
	}
	return (1);
}

t_env		*split_to_unset(t_ult *ult, char **arg)
{
	char	**splited_cmd;
	char	**tmp;

	splited_cmd = NULL;
	splited_cmd = arg;
	tmp = splited_cmd;
	tmp++;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '='))
			unset_error(*tmp);
		else
		{
			ult->ret = ft_unsetenv(&ult->env, *tmp);
			if (!ft_strncmp("PATH", *tmp, 4))
			{
				ult->hash_table ? hash_destroy(ult->hash_table) : NULL;
				ult->hash_table = NULL;
			}
		}
		tmp++;
	}
	return (ult->env);
}
