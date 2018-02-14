/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:32:52 by vfrolich          #+#    #+#             */
/*   Updated: 2018/02/09 12:00:36 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <lexer.h>

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

int 		new_env(char **arg_tab, t_env **env)
{
	char	**tmp;

	if (!arg_tab || !(*arg_tab))
		return (0);
	tmp = arg_tab;
	if (**tmp == '-')
		tmp++;
	while (*tmp && ft_strchr(*tmp, '='))
	{
		if (parse_var_setenv(*tmp) == 1)
		{
			free_env(env);
			return (1);
		}
		*env = add_env_one(*tmp, env);
		tmp++;
	}
	return (0);
}

int			launch_new_cmd(t_ult *ult, char **arg, t_env *tmp_env)
{
	t_lexer	*lexer;
	t_ult	*tmp_ult;

	tmp_ult = setting_tmp_ult(ult, tmp_env);
	tmp_ult->cmd = word_array_to_str(&arg[1]);
	tmp_ult->env = tmp_env;
	lexer = fill_lexer_env(tmp_ult, tmp_ult->cmd);
	ult->ret = start_prog(lexer, tmp_ult);
	ft_strdel(&tmp_ult->cmd);
	lex_free_all(lexer);
	hash_destroy(tmp_ult->hash_table);
	free(tmp_ult);
	return (ult->ret);
}

int			env_builtin(t_ult *ult, char **arg)
{
	t_env	*new;
	int		ret;

	ret = 0;
	if (!arg[1])
	{
		print_list(ult->env);
		return (0);
	}
	if ((check_opt(arg[1]) == 1))
		return (1);
	new = (!check_opt(arg[1])) ? NULL : envlist_cpy(ult->env);
	if (new_env(&arg[1], &new) == 1)
		return (1);	
	if (!arg[index_start_newtab(arg)])
	{
		print_list(new);
		ret = 0;
	}
	else
		ret = launch_new_cmd(ult, arg, new);
	free_env(&new);
	return (ret);
}
