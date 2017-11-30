/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:16:55 by vfrolich          #+#    #+#             */
/*   Updated: 2017/11/24 17:28:02 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static t_hashelem	*init_hash_one(char *binary, char *full_binary)
{
	t_hashelem		*dest;

	if (!(dest = (t_hashelem *)malloc(sizeof(t_hashelem))))
	{
		ft_putendl_fd("21sh : malloc error : abort.", 2);
		exit(1);
	}
	dest->bin_name = ft_strdup(binary);
	dest->full_bin_name = ft_strdup(full_binary);
	dest->next = NULL;
	return (dest);
}

void				hash_push(t_hashelem *newelem, t_hashelem **elemlist)
{
	t_hashelem		*tmp;

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

static DIR			*safe_opendir(char *path_string)
{
	DIR				*pathdir;

	if (access(path_string, F_OK) == -1)
	{
		ft_putstr_fd("21sh : bin directory ", 2);
		ft_putstr_fd(path_string, 2);
		ft_putendl_fd(" doesnt exists", 2);
		return (NULL);
	}
	if (access(path_string, X_OK) == -1)
	{
		ft_putstr_fd("21sh : bin directory ", 2);
		ft_putstr_fd(path_string, 2);
		ft_putendl_fd("21sh : bin directory ", 2);
		return (NULL);
	}
	pathdir = NULL;
	if (!(pathdir = opendir(path_string)))
	{
		ft_putendl_fd("21sh : malloc error on opendir call, abort.", 2);
		exit(1);
	}
	return (pathdir);
}

static void			get_bin_words(char *path_string, t_hashelem **hash_list)
{
	t_hashelem		*new;
	DIR				*pathdir;
	struct dirent	*file_info;
	char			*full_path;

	if (!(pathdir = safe_opendir(path_string)))
		return ;
	readdir(pathdir);
	readdir(pathdir);
	while ((file_info = readdir(pathdir)))
	{
		full_path = ft_strjoin(path_string, "/");
		full_path = ft_strjoin_free_one(&full_path, file_info->d_name);
		new = init_hash_one(file_info->d_name, full_path);
		hash_push(new, hash_list);
		ft_strdel(&full_path);
	}
	closedir(pathdir);
}

t_hashelem			*get_all_binwords(char *path_string)
{
	char			**path_strings;
	t_hashelem		*bin_words;
	t_hashelem		*new;
	char			**tmp;

	path_strings = ft_strsplit(path_string, ':');
	tmp = path_strings;
	bin_words = NULL;
	new = NULL;
	while (*tmp)
	{
		get_bin_words(*tmp, &bin_words);
		hash_push(new, &bin_words);
		tmp++;
	}
	free_tab(path_strings);
	return (bin_words);
}
