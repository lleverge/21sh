/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 12:42:28 by vfrolich          #+#    #+#             */
/*   Updated: 2017/11/30 15:42:32 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char			*hash_search(char *cmd, t_hashelem **table)
{
	int			index;
	t_hashelem	*tmp;

	index = 0;
	index = hash_it(cmd);
	tmp = NULL;
	if (index < 0 || index > 1020)
		return (NULL);
	tmp = table[index];
	if (!(table[hash_it(cmd)]))
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->bin_name, cmd))
			return (tmp->full_bin_name);
		tmp = tmp->next;
	}
	return (NULL);
}

void			hash_destroy_one(t_hashelem *elem)
{
	ft_strdel(&elem->bin_name);
	ft_strdel(&elem->full_bin_name);
	free(elem);
	elem = NULL;
}

void			hash_destroy(t_hashelem **table)
{
	t_hashelem	**tmp;
	int			index;
	t_hashelem	*tmp2;

	tmp = table;
	index = 0;
	if (!table)
		return ;
	while (index < 1021)
	{
		if (table[index])
		{
			while (table[index])
			{
				tmp2 = table[index]->next;
				hash_destroy_one(table[index]);
				table[index] = tmp2;
			}
		}
		index++;
	}
	table ? free(table) : NULL;
}

void			destroy_path_list(t_hashelem *path_list)
{
	t_hashelem	*tmp;

	while (path_list)
	{
		tmp = path_list->next;
		hash_destroy_one(path_list);
		path_list = tmp;
	}
}
