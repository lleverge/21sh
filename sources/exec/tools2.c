/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 14:29:56 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/24 12:29:49 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

int			list_size(t_env *env)
{
	int		size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

static int	is_validsubpath(char *sub_path, char *full_cmd_path)
{
	if (access(sub_path, F_OK) == -1)
	{
		ft_putstr_fd("21sh : no such file or directory: ", 2);
		ft_putendl_fd(full_cmd_path, 2);
		return (-1);
	}
	if (access(sub_path, X_OK) == -1)
	{
		ft_putstr_fd("21sh : permission denied: ", 2);
		ft_putendl_fd(full_cmd_path, 2);
		return (-1);
	}
	return (0);
}

int		path_access_checker(char *cmd_path)
{
	char **splited_cmd;
	char **tmp_arr;
	char *tmp;

	splited_cmd = ft_strsplit(cmd_path, '/');
	tmp_arr = splited_cmd;
	if (*cmd_path == '/')
		tmp = ft_strdup("/");
	else 
 		tmp = ft_strdup("");
	while (*splited_cmd)
	{
		tmp = ft_strjoin_free_one(&tmp, *splited_cmd);
		if (is_validsubpath(tmp, cmd_path) == -1)
		{
			free_tab(tmp_arr);
			ft_strdel(&tmp);
			return (-1);
		}
		tmp = ft_strjoin_free_one(&tmp, "/");
		splited_cmd++;
	}
	free_tab(tmp_arr);
	ft_strdel(&tmp);
	return (0);
}
