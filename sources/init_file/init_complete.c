/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:13:42 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/23 15:46:03 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

void			compl_push(t_compl *newelem, t_compl **elemlist)
{
	t_compl		*tmp;

	if (!(*elemlist))
	{
		*elemlist = newelem;
		return ;
	}
	tmp = *elemlist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newelem;
}

static t_compl	*init_compl_one(char *cmd)
{
	t_compl		*dest;

	dest = NULL;
	if (!(dest = (t_compl *)malloc(sizeof(t_compl))))
	{
		ft_putendl_fd("21sh : malloc error, abort.", 2);
		exit(3);
	}
	dest->name = ft_strdup(cmd);
	dest->next = NULL;
	return (dest);
}

static DIR			*safe_open(char *path_string)
{
	DIR				*pathdir;

	if (access(path_string, F_OK) == -1)
		return (NULL);
	if (access(path_string, X_OK) == -1)
		return (NULL);
	pathdir = NULL;
	if (!(pathdir = opendir(path_string)))
		return (NULL);
	return (pathdir);
}

static void			get_cmd(char *path, char *cmd, t_compl **list)
{
	t_compl 		*new;
	DIR				*pathdir;
	struct dirent 	*file_info;

	if (!(pathdir = safe_open(path)))
		return ;
	readdir(pathdir);
	readdir(pathdir);
	while ((file_info = readdir(pathdir)))
	{

		new = NULL;
		if (cmd)
		{
			if (!ft_strncmp(file_info->d_name, cmd, ft_strlen(cmd)))
				new = init_compl_one(file_info->d_name);
		}
		else
			new = init_compl_one(file_info->d_name);
		new ? compl_push(new, list) : NULL;
	}
	closedir(pathdir);
}

static t_compl 		*get_all_cmd(char *paths, char *cmd)
{
	char 		**path_strings;
	char		**tmp;
	t_compl		*dest;

	path_strings = ft_strsplit(paths, ':');
	tmp = path_strings;
	dest = NULL;
	while (*tmp)
	{
		get_cmd(*tmp, cmd, &dest);
		tmp++;
	}
	free(path_strings);
	return (dest);
}

t_compl			*init_cmd_compl(t_ult *ult, char *cmd)
{
	t_compl		*dest;
	char		*path_string;

	path_string = NULL;
	if (!(path_string = get_node_content(ult->env, "PATH")))
		return (NULL);
	dest = get_all_cmd(path_string, cmd);
	return (dest);
}
