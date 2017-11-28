/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:39:00 by vfrolich          #+#    #+#             */
/*   Updated: 2017/11/27 16:47:49 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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

static char			*alt_path_string(void)
{
	int				fd;
	char			*line;
	char			*dest;

	if ((fd = open("/etc/paths", O_RDONLY)) == -1)
		return (NULL);
	dest = strgen(1);
	line = NULL;
	while (get_next_line(fd, &line) != 0)
	{
		line = ft_strjoin_free_one(&line, ":");
		dest = ft_strjoin_free(&dest, &line);
	}
	close(fd);
	return (dest);
}

t_hashelem			*hash_init(void)
{
	char			*path_string;
	t_hashelem		*dest;

	path_string = NULL;
	path_string = getenv("PATH");
	if (!path_string)
		path_string = alt_path_string();
	if (!path_string)
	{
		ft_putendl_fd("21sh : open /etc/paths error , abort", 2);
		exit(1);
	}
	dest = get_all_binwords(path_string);
	return (dest);
}

void				hash_insert(t_hashelem *elem, t_hashelem **table)
{
	int				index;

	index = hash_it(elem->bin_name);
	elem->next = NULL;
	hash_push(elem, &table[index]);
}

t_hashelem			**table_init(void)
{
	t_hashelem **table;
	t_hashelem *tmp;
	t_hashelem *path_list;

	if (!(table = (t_hashelem **)malloc(sizeof(t_hashelem *) * 1021)))
	{
		ft_putendl_fd("21sh : malloc erroc on hash table init, abort.", 2);
		exit(1);
	}
	path_list = NULL;
	path_list = hash_init();
	while (path_list)
	{
		tmp = path_list->next;
		hash_insert(path_list, table);
		path_list = tmp;
	}
	return (table);
}
