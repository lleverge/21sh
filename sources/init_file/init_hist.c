/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:01:17 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/04 17:52:22 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

t_hist			*init_hist(t_hist *hist)
{
	t_hist		*new;

	if (!hist)
	{
		if (!(new = (t_hist *)malloc(sizeof(t_hist))))
		{
			ft_putendl_fd("error: hist malloc failed", 2);
			exit(-1);
		}
		new->index = 0;
		new->cmd = ft_strdup("");
		return (new);
	}
	else
		return (hist);
}
