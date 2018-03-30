/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 14:29:56 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/30 15:01:54 by lleverge         ###   ########.fr       */
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

static int	is_dir(char *path)
{
	struct stat *buffer;

	buffer = NULL;
	if (!(buffer = (struct stat *)malloc(sizeof(struct stat))))
	{
		ft_putendl_fd("malloc failed", 2);
		exit(3);
	}
	if (stat(path, buffer) == -1)
	{
		ft_putendl_fd("21sh : stat() failed", 2);
		return (-1);
	}
	if (S_ISDIR(buffer->st_mode))
	{
		ft_putstr_fd("21sh : ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": is a directory", 2);
		free(buffer);
		return (1);
	}
	free(buffer);
	return (0);
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

int			path_access_checker(char *cmd_path)
{
	char **splited_cmd;
	char **tmp_arr;
	char *tmp;

	splited_cmd = ft_strsplit(cmd_path, '/');
	tmp_arr = splited_cmd;
	tmp = (*cmd_path == '/') ? ft_strdup("/") : ft_strdup("");
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
	return (is_dir(cmd_path) ? -1 : 0);
}
