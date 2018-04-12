/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:30:11 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 15:59:16 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"
#include "../../includes/lexer.h"

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
