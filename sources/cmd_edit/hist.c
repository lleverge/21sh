/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:06:59 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/07 11:33:46 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void		hist_full(t_hist **hist)
{
	ft_strdel(&(*hist)->cmd);
	(*hist)->prev->next = NULL;
	(*hist)->prev = NULL;
	(*hist)->next = NULL;
	free(*hist);
}

void		fill_hist(t_hist **hist, char *cmd)
{
	t_hist		*tmp;
	int			i;

	i = 1;
	if (*hist)
	{
		tmp = *hist;
		while (tmp->next)
		{
			tmp = tmp->next;
			if (i == 50)
				hist_full(&tmp);
			i++;
		}
	}
	if (*cmd)
		add_hist(hist, cmd);
}

void		add_hist(t_hist **start, char *cmd)
{
	t_hist	*new;
	t_hist	*tmp;

	tmp = *start;
	if (!(new = (t_hist *)malloc(sizeof(t_hist))))
	{
		ft_putendl_fd("error: new hist malloc failed", 2);
		exit(-1);
	}
	new->cmd = ft_strdup(cmd);
	new->next = (*start)->next;
	if ((*start)->next)
		(*start)->next->prev = new;
	(*start)->next = new;
	new->prev = *start;
}
