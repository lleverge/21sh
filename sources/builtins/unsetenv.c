/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:18:54 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/16 16:12:43 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	free_env_one(t_env *env)
{
	ft_strdel(&env->name);
	ft_strdel(&env->content);
	free(env);
}

static int	count_env(t_env *envi)
{
	int result;

	result = 0;
	while (envi)
	{
		result++;
		envi = envi->next;
	}
	return (result);
}

static int	unset_one(t_env *envlist, char *name)
{
	t_env *tmp;

	if (!(ft_strcmp(envlist->next->name, name)))
	{
		tmp = envlist->next;
		envlist->next = envlist->next->next;
		free_env_one(tmp);
		return (0);
	}
	return (1);
}

static int	unset_env(char *name, t_env **envlist)
{
	t_env	*tmp;

	tmp = *envlist;
	while (tmp->next)
	{
		if (!unset_one(tmp, name))
			return (0);
		tmp = tmp->next;
	}
	if (!ft_strcmp(tmp->name, name))
	{
		if (count_env(*envlist) == 1)
		{
			free_env_one(*envlist);
			*envlist = NULL;
			return (0);
		}
		free_env_one(tmp);
		tmp = NULL;
		return (0);
	}
	return (1);
}

static void	unset_error(char *cmd)
{
	ft_putstr_fd("21sh: unset: '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

t_env		*split_to_unset(t_ult *ult)
{
	char	**splited_cmd;
	char	**tmp;

	splited_cmd = NULL;
	splited_cmd = ft_whitespace(ult->cmd);
	tmp = splited_cmd;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '='))
			unset_error(*tmp);
		else
		{
			ult->ret = unset_env(*tmp, &ult->env);
			if (!ft_strncmp("PATH", *tmp, 4))
			{
				ult->hash_table ? hash_destroy(ult->hash_table) : NULL;
				ult->hash_table = NULL;
			}
		}
		tmp++;
	}
	free_tab(splited_cmd);
	return (ult->env);
}
