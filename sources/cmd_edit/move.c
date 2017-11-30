/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:38:54 by lleverge          #+#    #+#             */
/*   Updated: 2017/11/30 15:45:46 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

static void		display_hist(t_prompt *prompt)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (prompt->cmd[i])
	{
		if (j == (int)prompt->win_size)
		{
			prompt->y++;
			j = 0;
		}
		ft_putchar(prompt->cmd[i]);
		i++;
		j++;
	}
}

void			down(t_prompt *prompt, char *buffer, t_ult *ult)
{
	if (T_DOWN)
	{
		if (ult->hist->prev)
		{
			reset(prompt);
			prompt->y = 0;
			ult->hist = ult->hist->prev;
			ft_strcpy(prompt->cmd, ult->hist->cmd);
			display_hist(prompt);
			prompt->i = ft_strlen(prompt->cmd);
			print_cursor(prompt, 1, prompt->i);
		}
	}
}

void			up(t_prompt *prompt, char *buffer, t_ult *ult)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (T_UP)
	{
		if (ult->hist->next)
		{
			reset(prompt);
			prompt->y = 0;
			ult->hist = ult->hist->next;
			ft_strcpy(prompt->cmd, ult->hist->cmd);
			display_hist(prompt);
			prompt->i = ft_strlen(prompt->cmd);
			print_cursor(prompt, 1, prompt->i);
		}
	}
}

void			left(t_prompt *prompt, char *buffer)
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

void			right(t_prompt *prompt, char *buffer)
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
