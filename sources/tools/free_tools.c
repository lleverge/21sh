/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:14:11 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/03 12:18:32 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

void		free_prompt(t_prompt **prompt)
{
	t_prompt *tmp;

	tmp = *prompt;
	tmp->i = 0;
	tmp->copy_mode = 0;
	tmp->cursor_start = 0;
	tmp->cursor_end = 0;
	if (tmp->copy_str)
		free(tmp->copy_str);
	tmp->win_size = 0;
	free(tmp);
	tmp = NULL;
}

void		free_env(t_env **head)
{
	t_env	*current;
	t_env	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		if (current->name)
			ft_strdel(&(current->name));
		if (current->content)
			ft_strdel(&(current->content));
		free(current);
		current = next;
	}
	*head = NULL;
}

void		free_tab(char **tabl)
{
	int		i;

	i = 0;
	while (tabl[i] != 0)
	{
		ft_strdel(&tabl[i]);
		i++;
	}
	free(tabl);
	tab = NULL;
}
