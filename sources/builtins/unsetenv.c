/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:18:54 by vfrolich          #+#    #+#             */
/*   Updated: 2017/12/10 16:27:33 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void	free_env_one(t_env *env)
{
	ft_strdel(&env->name);
	ft_strdel(&env->content);
	free(env);
}

static int	unset_env(char *name, t_env *envlist)
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

t_env		*split_to_unset(char *cmd, t_env *envlist)
{
	char	**splited_cmd;
	char	**tmp;

	splited_cmd = NULL;
	splited_cmd = ft_whitespace(cmd);
	tmp = splited_cmd;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '='))
		{
			ft_putstr("21sh: unset: '");
			ft_putstr(*tmp);
			ft_putendl("': not a valid identifier");
		}
		else
			unset_env(*tmp, envlist);
		tmp++;
	}
	free_tab(splited_cmd);
	return (envlist);
}
