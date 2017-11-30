/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:30:11 by vfrolich          #+#    #+#             */
/*   Updated: 2017/11/18 17:00:46 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>
#include <lexer.h>

int				*singleton_signal(void)
{
	static int	magic_int = 42;

	return (&magic_int);
}

void			sig_handler_heredoc(int sig)
{
	int			*magic_int;
	t_prompt	*prompt;

	magic_int = 0;
	prompt = NULL;
	prompt = stock_prompt(prompt, 1);
	if (sig == SIGINT)
	{
		magic_int = singleton_signal();
		*magic_int -= 1;
		reset_prompt_heredoc(prompt, 0);
		prompt_print(prompt, 1);
		tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
		tputs(tgetstr("ce", NULL), 1, ft_putchar_int);
	}
}
