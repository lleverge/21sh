/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:39:00 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/16 18:18:39 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

/*
** djb2 hash algorithm
*/

int					hash_it(char *cmd)
{
	int				c;
	char			*tmp;
	unsigned long	hash;

	tmp = cmd;
	hash = 5381;
	c = 0;
	while ((c = *tmp++))
		hash = (hash << 5) + hash + c;
	return (hash % 1021);
}

t_hashelem			*hash_init(t_env *envlist)
{
	char			*path_string;
	t_hashelem		*dest;

	path_string = NULL;
	if (!(path_string = get_node_content(envlist, "PATH")))
		return (NULL);
	dest = get_all_binwords(path_string);
	ft_strdel(&path_string);
	return (dest);
}

void				hash_insert(t_hashelem *elem, t_hashelem **table)
{
	int				index;

	index = hash_it(elem->bin_name);
	hash_push(init_hash_one(elem->bin_name, elem->full_bin_name),
			&table[index]);
}

static void			exit_tab(t_ult *ult)
{
	ft_putendl_fd("21sh: malloc error on hash table init, abort.", 2);
	exit_term(ult->term);
	exit(3);
}

t_hashelem			**table_init(t_env *envlist)
{
	t_hashelem	**table;
	t_hashelem	*tmp;
	t_hashelem	*path_list;
	t_ult		*ult;

	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!(table = (t_hashelem **)malloc(sizeof(t_hashelem *) * 1021)))
		exit_tab(ult);
	ft_bzero(table, sizeof(t_hashelem *) * 1021);
	path_list = NULL;
	if (!(path_list = hash_init(envlist)))
	{
		free(table);
		return (NULL);
	}
	tmp = path_list;
	while (path_list)
	{
		hash_insert(path_list, table);
		path_list = path_list->next;
	}
	path_list = tmp;
	destroy_path_list(path_list);
	return (table);
}
