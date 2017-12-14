/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:48:02 by vfrolich          #+#    #+#             */
/*   Updated: 2017/12/11 18:33:58 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void		env_push(t_env **envlist, t_env *envnode)
{
	t_env		*tmp;

	if (!(*envlist))
	{
		*envlist = envnode;
		return ;
	}
	tmp = *envlist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = envnode;
}

t_env			*set_env(t_env *env, char *name, char *value)
{
	t_env		*tmp;

	tmp = env;
	if (!name)
		return (env);
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			tmp->content ? ft_strdel(&tmp->content) : NULL;
			tmp->content = ft_strdup(value);
			return (env);
		}
		tmp = tmp->next;
	}
	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
	{
		ft_putendl_fd("21sh: malloc error, abort.", 2);
		exit(4);
	}
	tmp->name = ft_strdup(name);
	tmp->content = ft_strdup(value);
	tmp->next = NULL;
	env_push(&env, tmp);
	return (env);
}

t_env			*split_to_set(t_ult *ult)
{
	char		**splited_cmd;
	char		**tmp;
	char		*tmp_string;

	splited_cmd = NULL;
	splited_cmd = ft_whitespace(ult->cmd);
	tmp = splited_cmd;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '='))
		{
			tmp_string = ft_strsub(*tmp, 0, ft_strchr(*tmp, '=') - *tmp);
			ult->env = set_env(ult->env, tmp_string, ft_strchr(*tmp, '=') + 1);
			tmp_string ? ft_strdel(&tmp_string) : NULL;
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
