/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:14:11 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/25 17:15:45 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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

void		free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}
