/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:06:59 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/04 18:13:02 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void		hist_full(t_hist **hist)
{
	t_hist	*tmp;

	tmp = *hist;
	while (tmp->next)
		tmp = tmp->next;
	(*hist)->index = 0;
	ft_strdel(&(*hist)->cmd);
	(*hist)->next = NULL;
	free(*hist);
}

t_hist		*fill_hist(t_hist *hist, char *cmd)
{
	t_hist		*tmp;
	int			i;

	i = 1;
	if (hist)
	{
		tmp = hist;
		while (tmp->next)
		{
			if (i == 50)
				hist_full(&tmp);
			tmp = tmp->next;
			i++;
		}
	}
	hist = add_hist(hist, cmd);
	return (hist);
}

t_hist		*add_hist(t_hist *start, char *cmd)
{
	t_hist	*new;

	if (!(new = (t_hist *)malloc(sizeof(t_hist))))
	{
		ft_putendl_fd("error: new hist malloc failed", 2);
		exit(-1);
	}
	new->cmd = ft_strdup(cmd);
	new->index = 1;
	if (start == NULL)
		return (new);
	new->next = start;
	start = new;
	return (start);
}
