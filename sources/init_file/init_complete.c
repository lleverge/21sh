/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:13:42 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 15:54:32 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"
#include "../../includes/shell.h"

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

t_compl			*init_compl_one(char *cmd)
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
	dest->prev = NULL;
	return (dest);
}

static DIR		*safe_open(char *path_string)
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

static void		get_cmd(char *path, char *cmd, t_compl **list)
{
	t_compl			*new;
	DIR				*pathdir;
	struct dirent	*file_info;

	if (!(pathdir = safe_open(path)))
		return ;
	readdir(pathdir);
	readdir(pathdir);
	while ((file_info = readdir(pathdir)))
	{
		new = NULL;
		if (ft_strlen(cmd))
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

t_compl			*get_all_cmd(char *paths, char *cmd)
{
	char		**path_strings;
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
	if (dest)
		dest->cursored = 1;
	free_tab(path_strings);
	return (dest);
}
