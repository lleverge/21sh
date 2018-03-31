/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:38:18 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/31 13:23:12 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

void	free_choice_one(t_compl *elem)
{
	ft_strdel(&elem->name);
	free(elem);
	elem = NULL;
}

void	free_all_choices(t_compl *elem)
{
	t_compl *tmp;
	size_t	to_del;

	to_del = count_entries(elem);
	while (to_del)
	{
		tmp = elem->next;
		free_choice_one(elem);
		elem = tmp;
		to_del--;
	}
}
