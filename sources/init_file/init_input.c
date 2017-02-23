/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:14:21 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/23 14:17:00 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

t_input				*init_input(void)
{
	t_input		*input;

	if (!(input = (t_input *)malloc(sizeof(t_input))))
	{
		ft_putendl_fd("error: struct input malloc failed", 2);
		exit(-1);
	}
	input->curs = init_cursor();
	input->cmd_line = ft_strdup("");
	input->cp = NULL;
	input->lprom = 0;
	return (input);
}
