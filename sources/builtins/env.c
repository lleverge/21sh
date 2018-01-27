/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:32:52 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/27 15:30:12 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

int			parse_var_setenv(char *arg)
{
	if (ft_strchr(arg, '=') == arg)
	{
		ft_putstr_fd("env : setenv ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(" : Invalid argument", 2);
		return (1);
	}
	return (0);
}

t_env		*add_env_one(char *arg, t_env **env)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = NULL;
	if (ft_strchr(arg, '=') == arg)
		return (*env);
	tmp_name = ft_strsub(arg, 0, ft_strchr(arg, '=') - arg);
	tmp_value = NULL;
	tmp_value = ft_strchr(arg, '=') + 1;
	*env = set_env(env, tmp_name, tmp_value);
	ft_strdel(&tmp_name);
	return (*env);
}

t_env		*new_env(char **arg_tab, t_env **env)
{
	char	**tmp;

	if (!arg_tab || !(*arg_tab))
		return (*env);
	tmp = arg_tab;
	while (*tmp && ft_strchr(*tmp, '='))
	{
		if (parse_var_setenv(*tmp) == 1)
		{
			free_env(env);
			return (NULL);
		}
		*env = add_env_one(*tmp, env);
		tmp++;
	}
	return (*env);
}

int			check_opt(char *opt)
{
	if (*opt != '-')
		return (2);
	if (opt[1] && opt[1] == 'i')
		return (0);
	else if (opt[1])
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(opt[1], 2);
		ft_putchar_fd('\n', 2);
		ft_putendl_fd("usage : env [-i] [name=value ...] [utility [argument .\
..]]", 2);
	}
	return (1);
}

int			env_builtin(t_process *proc, t_ult *ult, char **arg)
{
	t_env	*tmp;
	t_env	*new;

	tmp = ult->env;
	if (!proc)
		return (1);
	if (!arg[1])
	{
		new = envlist_cpy(ult->env);
		print_list(new);
		free_env(&new);
		return (0);
	}
	if ((check_opt(arg[1]) == 1))
		return (1);
	if (!check_opt(arg[1]))
		new = NULL;
	else
		new = envlist_cpy(ult->env);
	if (!(new = new_env(&arg[2], &new)))
		return (1);
	print_list(new);
	free_env(&new);
	return (0);
}
