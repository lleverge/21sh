/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updown.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:17:56 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/12 15:45:12 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"

void		down_line(t_prompt *prompt, char *buffer)
{
	if (DOWN_CMD && ft_strlen(prompt->cmd) > prompt->win_size)
	{
		if ((size_t)prompt->i <= ft_strlen(prompt->cmd) -
			(prompt->win_size - 3))
			prompt->i = prompt->i + prompt->win_size;
		else
			prompt->i = ft_strlen(prompt->cmd);
		prompt_print(prompt, 1);
	}
}

void		up_line(t_prompt *prompt, char *buffer)
{
	if (UP_CMD && ft_strlen(prompt->cmd) >
		prompt->win_size && (size_t)prompt->i > prompt->win_size)
	{
		prompt->i = prompt->i - prompt->win_size;
		prompt_print(prompt, 1);
	}
	else if (UP_CMD && prompt->i < (int)prompt->win_size)
	{
		prompt->i = 0;
		prompt_print(prompt, 1);
	}
}
