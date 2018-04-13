/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   homend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:11:37 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/13 16:02:42 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"

void		next_word(t_prompt *prompt, char *buffer)
{
	if (NEXT_WORD)
	{
		while (prompt->cmd[prompt->i] &&
			ft_isspace(prompt->cmd[prompt->i]) == 0)
			prompt->i++;
		while (prompt->cmd[prompt->i] &&
			ft_isspace(prompt->cmd[prompt->i]) == 1)
			prompt->i++;
		prompt_print(prompt, 1);
	}
}

void		previous_word(t_prompt *prompt, char *buffer)
{
	if (PREV_WORD)
	{
		while (prompt->i > 0 &&
			ft_isspace(prompt->cmd[prompt->i]) == 0)
			prompt->i--;
		while (prompt->i > 0 &&
			ft_isspace(prompt->cmd[prompt->i]) == 1)
			prompt->i--;
		prompt_print(prompt, 1);
	}
}

void		home(t_prompt *prompt, char *buffer)
{
	if (T_HOME)
	{
		while (prompt->i > 0)
			prompt->i--;
		prompt_print(prompt, 1);
	}
}

void		end(t_prompt *prompt, char *buffer)
{
	if (T_END)
	{
		while (prompt->cmd[prompt->i])
			prompt->i++;
		prompt_print(prompt, 1);
	}
}
