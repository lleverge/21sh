/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_complete2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:25:34 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/23 17:38:25 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

static void		add_prev(t_compl *list)
{
	t_compl 	*tmp;
	t_compl		*tmp2;

	tmp = list;
	tmp2 = tmp;
	tmp = tmp->next;
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
	add_prev(dest);
	return (dest);
}
