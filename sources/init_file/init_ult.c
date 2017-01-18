/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:00:44 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/18 13:05:38 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

t_ult			*init_ult(t_ult *ult, char **environ)
{
	if (!(ult = (t_ult *)malloc(sizeof(t_ult))))
	{
		ft_putendl_fd("error: ult struct malloc failed", 2);
		return (NULL);
	}
	ult->env = NULL;
	ult->term = NULL;
	return (ult);
}
