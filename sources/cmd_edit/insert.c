/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:35:51 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/03 18:36:49 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void		delete(t_prompt *prompt, char *buffer)
{
	if (T_DEL && prompt->cmd[prompt->i])
	{
		ft_memmove(prompt->cmd + prompt->i, prompt->cmd + prompt->i + 1,
				   ft_strlen(prompt->cmd + prompt->i + 1) + 1);
		prompt_print(prompt, 1);
	}
}

void		backspace(t_prompt *prompt, char *buffer)
{
	if (BACK_SPACE && prompt->i > 0)
	{
		prompt->i--;
		ft_memmove(prompt->cmd + prompt->i, prompt->cmd + prompt->i + 1,
				   ft_strlen(prompt->cmd + prompt->i + 1) + 1);
		prompt_print(prompt, 1);
	}
}

void		space(t_prompt *prompt, char *buffer)
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

void		charac(t_prompt *prompt, char *buffer)
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
