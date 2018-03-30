/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:23:07 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/30 11:20:00 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <builtins.h>

static int		go_home(t_env **env)
{
	char		*home;
	char		*old;

	if (!(home = get_node_content(*env, "HOME")))
	{
		ft_putendl_fd("cd: HOME isnt defined", 2);
		return (1);
	}
	if (access(home, X_OK) == -1)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putendl_fd(home, 2);
		ft_strdel(&home);
		return (1);
	}
	old = get_cdir(*env);
	chdir(home);
	unset_env("OLDPWD", *env);
	set_env(env, "OLDPWD", old);
	unset_env("PWD", *env);
	set_env(env, "PWD", home);
	ft_strdel(&old);
	ft_strdel(&home);
	return (0);
}

static int		change_dir(t_env **env, char *path)
{
	char		*old;
	char		*tmp;

	old = get_cdir(*env);
	if (env)
	{
		unset_env("OLDPWD", *env);
		set_env(env, "OLDPWD", old);
	}
	old ? ft_strdel(&old) : NULL;
	chdir(path);
	tmp = get_cdir(*env);
	if (env && *env)
	{
		unset_env("PWD", *env);
		set_env(env, "PWD", tmp);
	}
	ft_strdel(&tmp);
	return (0);
}

static int		err_cd_handle(t_env **env, char **arg)
{
	struct stat stats;

	if (stat(arg[0], &stats) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(arg[0], 2);
		return (1);
	}
	else if (!(S_ISDIR(stats.st_mode)))
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(arg[0], 2);
		return (1);
	}
	else if (access(arg[0], X_OK) == -1)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putendl_fd(arg[0], 2);
		return (1);
	}
	return (change_dir(env, arg[0]));
}

static int		prev_dir(t_env **env)
{
	char		*old;
	char		*tmp;

	tmp = get_cdir(*env);
	if (!(old = get_node_content(*env, "OLDPWD")))
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		tmp ? ft_strdel(&tmp) : NULL;
		return (1);
	}
	ft_putendl(old);
	if (env && *env)
	{
		unset_env("OLDPWD", *env);
		set_env(env, "OLDPWD", tmp);
	}
	tmp ? ft_strdel(&tmp) : NULL;
	chdir(old);
	if (env && *env)
	{
		unset_env("PWD", *env);
		set_env(env, "PWD", old);
	}
	ft_strdel(&old);
	return (0);
}

int				ft_cd(t_env **env, char **arg)
{
	char		*home;
	char		*tmp;

	if (!ft_strlen(arg[1]) || !ft_strcmp(arg[1], "~"))
		return (go_home(env));
	else if (!ft_strcmp(arg[1], "-"))
		return (prev_dir(env));
	else if (arg[0] && arg[1] && arg[2])
	{
		ft_putendl_fd("cd: multiple directory entry", 2);
		return (1);
	}
	if (!ft_strncmp(arg[1], "~/", 2))
	{
		if ((home = get_data(*env, "HOME")))
		{
			tmp = ft_strsub(arg[1], 1, ft_strlen(arg[1]) - 1);
			arg[1] = ft_strjoin(home, tmp);
			ft_strdel(&tmp);
			return (err_cd_handle(env, &arg[1]));
		}
	}
	return (err_cd_handle(env, &arg[1]));
}
