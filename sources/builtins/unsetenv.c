/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:18:54 by vfrolich          #+#    #+#             */
/*   Updated: 2017/12/11 22:57:58 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void	free_env_one(t_env *env)
{
	ft_strdel(&env->name);
	ft_strdel(&env->content);
	free(env);
}

int			unset_env(char *name, t_env *envlist)
{
	t_env	*tmp;
	t_env	*start;

	start = envlist;
	if (!name || !start)
		return (1);
	while (envlist->next)
	{
		if (!(ft_strcmp(envlist->next->name, name)))
		{
			tmp = envlist->next;
			envlist->next = envlist->next->next;
			free_env_one(tmp);
			envlist = start;
			return (0);
		}
		envlist = envlist->next;
	}
	envlist = start;
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
			ult->ret = unset_env(*tmp, ult->env);
			if (!ft_strncmp("PATH", *tmp, 4))
			{
				hash_destroy(ult->hash_table);
				ult->hash_table = table_init(ult->env);
			}
		}
		tmp++;
	}
	free_tab(splited_cmd);
	return (ult->env);
}
