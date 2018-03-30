/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_list_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:26:42 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/30 14:01:12 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void		quote_push(t_quote *elem, t_quote **elemlist)
{
	t_quote	*tmp;

	if (!(*elemlist))
	{
		*elemlist = elem;
		return ;
	}
	tmp = *elemlist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
}

t_quote		*quote_list_init(char *cmd)
{
	t_quote *new;
	t_quote *head;
	char	*sub_cmd;

	if (!ft_strchr(cmd, '\'') && !ft_strchr(cmd, '"'))
		return (NULL);
	head = quoted_list_init_one(cmd, cmd);
	sub_cmd = &cmd[head->quotes[1]] + 1;
	new = NULL;
	while (ft_strchr(sub_cmd, '\'') || ft_strchr(sub_cmd, '"'))
	{
		new = quoted_list_init_one(sub_cmd, cmd);
		sub_cmd = &sub_cmd[new->quotes[1]] + 1;
		ft_putendl(sub_cmd);
		quote_push(new, &head);
	}
	return (head);
}

void		quote_destroy(t_quote *quote_list)
{
	t_quote	*tmp;

	while (quote_list)
	{
		tmp = quote_list->next;
		free(quote_list);
		quote_list = tmp;
	}
	quote_list = NULL;
}
