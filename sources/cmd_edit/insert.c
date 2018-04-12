/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:35:51 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/12 15:45:50 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

void			print_backsp(t_prompt *prompt, int show_cursor)
{
	int		i;
	int		cursor_flag;
	size_t	j;

	i = 0;
	j = 0;
	cursor_flag = 0;
	reset(prompt);
	prompt->y = 0;
	while (prompt->cmd[i])
	{
		if ((j == prompt->win_size - 4 && prompt->y == 0) ||
			(j == prompt->win_size && prompt->y != 0))
		{
			prompt->y++;
			j = 0;
		}
		if (i == prompt->i && show_cursor == 1)
		{
			cursor_flag = 1;
			tputs(tgetstr("mr", NULL), 1, ft_putchar_int);
			ft_putchar(prompt->cmd[i]);
			tputs(tgetstr("me", NULL), 1, ft_putchar_int);
		}
		else
			ft_putchar(prompt->cmd[i]);
		i++;
		j++;
	}
	if (cursor_flag == 0)
		print_cursor(prompt, show_cursor, i);
}

void			delete(t_prompt *prompt, char *buffer)
{
	if (T_DEL && prompt->cmd[prompt->i])
	{
		if ((size_t)prompt->i == ft_strlen(prompt->cmd))
			prompt->i--;
		ft_memmove(prompt->cmd + prompt->i, prompt->cmd + prompt->i + 1,
				ft_strlen(prompt->cmd + prompt->i + 1) + 1);
		print_backsp(prompt, 1);
	}
}

void			backspace(t_prompt *prompt, char *buffer)
{
	if (BACK_SPACE && prompt->i > 0)
	{
			prompt->i--;
		ft_memmove(prompt->cmd + prompt->i, prompt->cmd + prompt->i + 1,
				ft_strlen(prompt->cmd + prompt->i + 1) + 1);
		print_backsp(prompt, 1);
	}
}

void			space(t_prompt *prompt, char *buffer)
{
	if (WHITE_SP && prompt->i < 1999)
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
	if (CHAR && prompt->i < 1999)
	{
		ft_memmove(prompt->cmd + prompt->i + 1, prompt->cmd + prompt->i,
				ft_strlen(prompt->cmd + prompt->i) + 1);
		prompt->cmd[prompt->i] = *buffer;
		prompt->i++;
		prompt_print(prompt, 1);
	}
}
