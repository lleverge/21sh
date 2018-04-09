/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_complete3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 20:09:48 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/09 13:24:11 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

DIR			*safe_open_dir(char *path_string)
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

static t_compl *on_empty(void)
{
	t_compl			*list;
	t_compl			*new;
	DIR				*curr_dir;
	struct dirent 	*file_info;

	if (!(curr_dir = safe_open_dir(".")))
		return (NULL);
	list = NULL;
	while ((file_info = readdir(curr_dir)))
	{
		new = NULL;
		if (ft_strlen(file_info->d_name) && file_info->d_name[0] != '.')
			new = init_compl_one(file_info->d_name);
		new ? compl_push(new, &list) : NULL;
	}
	closedir(curr_dir);
	return (list);
}

static t_compl *on_word(char *word)
{
	t_compl			*list;
	t_compl			*new;
	DIR				*curr_dir;
	struct dirent 	*file_info;

	if (!(curr_dir = safe_open_dir(".")))
		return (NULL);
	list = NULL;
	while ((file_info = readdir(curr_dir)))
	{
		new = NULL;
		if (!ft_strncmp(file_info->d_name, word, ft_strlen(word)))
			new = init_compl_one(file_info->d_name);
		new ? compl_push(new, &list) : NULL;
	}
	closedir(curr_dir);
	return (list);
}

t_compl	*classic_compl(t_prompt *prompt)
{
	t_compl *new;
	char	*word;

	word = word_detect(prompt);
	new = NULL;
	if (!ft_strlen(word))
	{
		ft_strdel(&word);
		new = on_empty();
		new ? add_prev(new) : NULL;
		new->cursored = 1;
		return (new);
	}
	new = on_word(word);
	new ? add_prev(new) : NULL;
	if (new)
		new->cursored = 1;
	if ((new && compl_dir_needed(new)) || (!new && !access(word, F_OK | X_OK)))
		dir_handle(&new, word);
	word ? ft_strdel(&word) : NULL;
	return (new);
}
