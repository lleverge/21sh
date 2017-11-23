/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:39:00 by vfrolich          #+#    #+#             */
/*   Updated: 2017/11/23 22:13:57 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

/* djb2 hash algorithm */
int		hash_it(char *cmd)
{
	int 		c;
	char 		*tmp;
	unsigned long hash = 5381;

	tmp = cmd;
	c = 0;
	while ((c = *tmp++))
		hash = (hash << 5) + hash + c;
	return (hash%1021);
}

static char 		*alt_path_string()
{
	int 			fd;
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

t_list				*hash_init()
{
	char 			*path_string;
	t_hashelem		*dest;
	int 			count;

	path_string = NULL;
	path_string = getenv("PATH");
	if (!path_string)
		path_string = alt_path_string();
	if (!path_string)
	{
		ft_putendl_fd("21sh : open /etc/paths error , abort", 2);
		exit (1);
	}
	dest = get_all_binwords(path_string);
	count = 0;
	while (dest)
	{
		ft_putendl(dest->full_bin_name);
		dest = dest->next;
		count++;
	}
	return (NULL);
}
