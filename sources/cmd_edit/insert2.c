/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:20:55 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/16 17:23:22 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

void			space(t_prompt *prompt, char *buffer)
{
	if (WHITE_SP && ft_strlen(prompt->cmd) < 1999)
	{
		ft_memmove(prompt->cmd + prompt->i + 1, prompt->cmd + prompt->i,
				ft_strlen(prompt->cmd + prompt->i) + 1);
		prompt->cmd[prompt->i] = ' ';
		prompt->i++;
		prompt_print(prompt, 1);
	}
}

void			charac(t_prompt *prompt, char *buffer)
{
	if (CHAR && ft_strlen(prompt->cmd) < 1999)
	{
		ft_memmove(prompt->cmd + prompt->i + 1, prompt->cmd + prompt->i,
				ft_strlen(prompt->cmd + prompt->i) + 1);
		prompt->cmd[prompt->i] = *buffer;
		prompt->i++;
		prompt_print(prompt, 1);
	}
}
