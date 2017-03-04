/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:38:54 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/04 16:02:48 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void		down(t_prompt *prompt, char *buffer)
{
	if (T_DOWN)
	{
		prompt->i = ft_strlen(prompt->cmd);
		prompt_print(prompt, 1);
	}
}

void		up(t_prompt *prompt, char *buffer)
{
	if (T_UP)
	{
		prompt->i = ft_strlen(prompt->cmd);
		prompt_print(prompt, 1);
	}
}

void		left(t_prompt *prompt, char *buffer)
{
	if (T_LEFT && prompt->i > 0)
	{
		if (prompt->copy_mode == 1 && prompt->i == prompt->cursor_start)
			prompt->cursor_start--;
		else if (prompt->copy_mode == 1 &&
				prompt->cursor_start < prompt->cursor_end)
			prompt->cursor_end--;
		prompt->i--;
		prompt_print(prompt, 1);
	}
}

void		right(t_prompt *prompt, char *buffer)
{
	if (T_RIGHT && prompt->cmd[prompt->i])
	{
		if (prompt->copy_mode == 1 && prompt->i == prompt->cursor_end)
			prompt->cursor_end++;
		else if (prompt->copy_mode == 1 &&
				prompt->cursor_start < prompt->cursor_end)
			prompt->cursor_start++;
		prompt->i++;
		prompt_print(prompt, 1);
	}
}
