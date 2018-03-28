/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 16:31:33 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/27 18:33:02 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

static t_compl	*search_selected(t_compl *list)
{
	t_compl *tmp;

	tmp = list;
	if (tmp->cursored == 1)
		return (tmp);
	tmp = tmp->next;
	while (tmp != list)
	{
		if (tmp->cursored == 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	select_next(t_compl *list)
{
	t_compl *selected;

	selected = NULL;
	if (!(selected = search_selected(list)))
	{
		ft_putendl_fd("no member selected in completion", 2);
		return ;
	}
	selected->cursored = 0;
	selected->next->cursored = 1;
}

void	select_prev(t_compl *list)
{
	t_compl *selected;

	selected = NULL;
	if (!(selected = search_selected(list)))
	{
		ft_putendl_fd("no member selected in completion", 2);
		return ;
	}
	selected->cursored = 0;
	selected->prev->cursored = 1;
}

void	do_selection(t_compl *list, t_prompt *prompt)
{
	t_compl *selected;

	selected = search_selected(list);
	select_in_prompt(selected->name, prompt);
}