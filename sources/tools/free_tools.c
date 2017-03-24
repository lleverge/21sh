/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:14:11 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/24 15:26:35 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <lexer.h>

void		free_lexer(t_lexer **lexer)
{
	t_lexer *current;
	t_lexer *next;

	current = *lexer;
	while (current)
	{
		next = current->next;
		if (current->content)
			ft_strdel(&(current->content));
		if (current->cmd)
			free_tab(current->cmd);
		current->token_id = 0;
		current->prev = NULL;
		current->next = NULL;
		free(current);
		current = next;
	}
	*lexer = NULL;
}

void		free_prompt(t_prompt **prompt)
{
	t_prompt *tmp;

	tmp = *prompt;
	tmp->i = 0;
	tmp->copy_mode = 0;
	tmp->cursor_start = 0;
	tmp->cursor_end = 0;
	if (tmp->copy_str)
		ft_strdel(&(tmp->copy_str));
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
