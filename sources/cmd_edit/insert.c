/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:35:51 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/04 17:42:53 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

static void		print_backsp(t_prompt *prompt, int show_cursor, t_ult *ult)
{
	int		i;
	size_t	j;

	i = 0;
	reset_prompt2(prompt, ult);
	j = 3;
	while (prompt->cmd[i])
	{
		tputs(tgetstr("me", NULL), 1, ft_putchar_int);
		if (i == prompt->i && show_cursor == 1)
			tputs(tgetstr("mr", NULL), 1, ft_putchar_int);
		if (prompt->copy_mode == 1 && i >= prompt->cursor_start
			&& i <= prompt->cursor_end)
			tputs(tgetstr("mr", NULL), 1, ft_putchar_int);
		ft_putchar(prompt->cmd[i]);
		j++;
		if (j >= prompt->win_size)
		{
			j = 0;
		}
		i++;
	}
	print_cursor(prompt, show_cursor, i);
}

void			delete(t_prompt *prompt, char *buffer)
{
	if (T_DEL && prompt->cmd[prompt->i])
	{
		ft_memmove(prompt->cmd + prompt->i, prompt->cmd + prompt->i + 1,
				ft_strlen(prompt->cmd + prompt->i + 1) + 1);
		prompt_print(prompt, 1);
	}
}

void			backspace(t_prompt *prompt, char *buffer, t_ult *ult)
{
	if (BACK_SPACE && prompt->i > 0)
	{
		prompt->i--;
		ft_memmove(prompt->cmd + prompt->i, prompt->cmd + prompt->i + 1,
				ft_strlen(prompt->cmd + prompt->i + 1) + 1);
		print_backsp(prompt, 1, ult);
	}
}

void			space(t_prompt *prompt, char *buffer)
{
	if (WHITE_SP)
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
	if (CHAR)
	{
		ft_memmove(prompt->cmd + prompt->i + 1, prompt->cmd + prompt->i,
				ft_strlen(prompt->cmd + prompt->i) + 1);
		prompt->cmd[prompt->i] = *buffer;
		prompt->i++;
		prompt_print(prompt, 1);
	}
}
