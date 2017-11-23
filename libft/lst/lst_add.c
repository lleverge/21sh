/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:42:24 by vfrolich          #+#    #+#             */
/*   Updated: 2017/06/22 19:17:19 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	lst_add(t_list *new, t_list **start)
{
	t_list *tmp;

	tmp = NULL;
	if (!new)
		return ;
	if (start)
		tmp = *start;
	if (!tmp)
	{
		*start = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
