/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_complete2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:25:34 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/09 13:43:42 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

void		add_prev(t_compl *list)
{
	t_compl 	*tmp;
	t_compl		*tmp2;

	tmp = list;
	tmp2 = tmp;
	tmp = tmp->next;
	if (tmp2 == tmp)
	{
		list->prev = list;
		return ;
	}
	while (tmp)
	{
		tmp->prev = tmp2;
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp2->next= list;
	list->prev = tmp2;
}

t_compl			*init_cmd_compl(t_ult *ult, char *cmd)
{
	t_compl		*dest;
	char		*path_string;

	path_string = NULL;
	if (!(path_string = get_node_content(ult->env, "PATH")))
		return (NULL);
	dest = get_all_cmd(path_string, cmd);
	if (dest)
		add_prev(dest);
	ft_strdel(&path_string);
	return (dest);
}

static t_compl		*init_on_dir(char *path_dir)
{
	DIR				*open_dir;
	t_compl			*list;
	t_compl			*new;
	struct dirent	*file_info;
	char			*buff;

	if (!(open_dir = safe_open_dir(path_dir)))
		return (NULL);
	list = NULL;
	buff = NULL;
	while ((file_info = readdir(open_dir)))
	{
		new = NULL;
		if (file_info->d_name[0] != '.')
		{
			buff = ft_strjoin(path_dir, file_info->d_name);
			new = init_compl_one(buff);
			ft_strdel(&buff);
		}
		new ? compl_push(new, &list) : NULL;
	}
	closedir(open_dir);
	if (list)
		list->cursored = 1;
	return (list);
}

int		compl_dir_needed(t_compl *list)
{	
	struct	stat *file_info;

	file_info = NULL;
	if (count_entries(list) > 1 || access(list->name, F_OK | X_OK) == -1)
		return (0);
	if (!(file_info = (struct stat *)malloc(sizeof(struct stat))))
	{
		ft_putendl_fd("21sh: malloc error", 2);
		exit(3);
	}
 	if (lstat(list->name, file_info) == -1)
 	{
 		free(file_info);
 		return (0);
 	}
 	free(file_info);
	return (S_ISDIR(file_info->st_mode) ? 1 : 0);
}

void	dir_handle(t_compl **list, char *word)
{
	char	*buffer;
	t_compl	*tmp;

	if (!word || !ft_strlen(word))
		return ;
	tmp = *list;
	if ((!list || !*list) && (ft_strchr(word , '/') && !access(word, F_OK | X_OK)))
	{
		if (word[ft_strlen(word) - 1] != '/')
		{
			buffer = ft_strjoin(word, "/");
			*list = init_on_dir(buffer);
			ft_strdel(&buffer);	
		}
		else
			*list = init_on_dir(word);
	}
	else if (!ft_strcmp(tmp->name, word))
	{
		buffer = ft_strdup(tmp->name);
		ft_strdel(&tmp->name);
		tmp->name = ft_strjoin_free_one(&buffer, "/");
	}
	*list ? add_prev(*list) : NULL;
}
