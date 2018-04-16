/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:01:17 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/16 14:59:15 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

t_hist			*init_hist(t_hist *hist)
{
	t_hist		*new;
	t_ult		*ult;

	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!hist)
	{
		if (!(new = (t_hist *)malloc(sizeof(t_hist))))
		{
			ft_putendl_fd("error: hist malloc failed", 2);
			exit_term(ult->term);
			exit(3);
		}
		new->cmd = ft_strdup("");
		new->prev = NULL;
		new->next = NULL;
		return (new);
	}
	else
		return (hist);
}
