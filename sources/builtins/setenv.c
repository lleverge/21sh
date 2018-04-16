/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:48:02 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/16 18:15:26 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

static int			invalid_identifier(char *cmd)
{
	if (ft_strchr(cmd, '=') == cmd)
	{
		ft_putstr_fd("setenv :", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" : Invalid argument", 2);
		return (1);
	}
	return (0);
}

static void			env_push(t_env **envlist, t_env *envnode)
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

static t_env		*new_env_one(char *name, char *value)
{
	t_env		*tmp;
	t_ult		*ult;

	tmp = NULL;
	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
	{
		ft_putendl_fd("21sh: malloc error, abort.", 2);
		exit_term(ult->term);
		exit(3);
	}
	tmp->name = ft_strdup(name);
	tmp->content = ft_strdup(value);
	tmp->next = NULL;
	return (tmp);
}

t_env				*set_env(t_env **env, char *name, char *value)
{
	t_env		*tmp;

	tmp = *env;
	if (!name)
		return (*env);
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			tmp->content ? ft_strdel(&tmp->content) : NULL;
			tmp->content = ft_strdup(value);
			return (*env);
		}
		tmp = tmp->next;
	}
	tmp = new_env_one(name, value);
	env_push(env, tmp);
	return (*env);
}

t_env				*add_all_env(t_ult *ult, char **cmd)
{
	char		**tmp;
	char		*tmp_string;

	tmp = cmd;
	tmp_string = NULL;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '=') && !invalid_identifier(*tmp))
		{
			tmp_string = ft_strsub(*tmp, 0, ft_strchr(*tmp, '=') - *tmp);
			ult->env = set_env(&ult->env, tmp_string, ft_strchr(*tmp, '=') + 1);
			tmp_string ? ft_strdel(&tmp_string) : NULL;
			if (!ft_strncmp("PATH", *tmp, 4))
			{
				hash_destroy(ult->hash_table);
				ult->hash_table = table_init(ult->env);
			}
		}
		tmp++;
	}
	return (ult->env);
}
