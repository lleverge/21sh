/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:35:51 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/08 13:01:49 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void			print_backsp(t_prompt *prompt, int show_cursor)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	reset(prompt);
	prompt->y = 0;
	while (prompt->cmd[i])
	{
		if (j == prompt->win_size - 4 && prompt->y == 0)
		{
			prompt->y++;
			j = 0;
		}
		else if (j == prompt->win_size && prompt->y != 0)
		{
			prompt->y++;
			j = 0;
		}
		ft_putchar(prompt->cmd[i]);
		i++;
		j++;
	}
	prompt->i = ft_strlen(prompt->cmd);
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
