/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:22:27 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/27 16:25:20 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void			reset_prompt(t_prompt *prompt)
{
	size_t		i;
	size_t		j;

	j = 3;
	i = 0;
	prompt->y = 0;
	tputs(tgetstr("vi", NULL), 1, ft_putchar_int);
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	while (i < ft_strlen(prompt->cmd))
	{
		if (j >= prompt->win_size)
		{
			tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
			tputs(tgetstr("up", NULL), 1, ft_putchar_int);
			j = 0;
		}
		j++;
		i++;
	}
	tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
	color(RED, "$> ");
	color(RESET, "");
}

void			print_cursor(t_prompt *prompt, int show_cursor, int i)
{
	if (i == prompt->i && show_cursor == 1)
	{
		tputs(tgetstr("mr", NULL), 1, ft_putchar_int);
		ft_putchar(' ');
	}
	tputs(tgetstr("me", NULL), 1, ft_putchar_int);
}

void			prompt_print(t_prompt *prompt, int show_cursor)
{
	int		i;
	size_t	j;

	i = 0;
	!prompt->heredoc ? reset_prompt(prompt) : reset_prompt_heredoc(prompt, 1);
	j = 3;
	while (prompt->cmd[i])
	{
		tputs(tgetstr("me", NULL), 1, ft_putchar_int);
		if (i == prompt->i && show_cursor == 1)
			tputs(tgetstr("mr", NULL), 1, ft_putchar_int);
		ft_putchar(prompt->cmd[i]);
		j++;
		if (j >= prompt->win_size)
		{
			ft_putendl("");
			tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
			j = 0;
			prompt->y++;
		}
		i++;
	}
	print_cursor(prompt, show_cursor, i);
}

void			prompt_shell(t_prompt *prompt, char *buffer, t_ult *ult)
{
	main_auto(prompt, buffer, ult);
	charac(prompt, buffer);
	space(prompt, buffer);
	down_line(prompt, buffer);
	up_line(prompt, buffer);
	backspace(prompt, buffer);
	delete(prompt, buffer);
	left(prompt, buffer);
	right(prompt, buffer);
	up(prompt, buffer, ult);
	down(prompt, buffer, ult);
	home(prompt, buffer);
	previous_word(prompt, buffer);
	next_word(prompt, buffer);
	end(prompt, buffer);
	cut(prompt, buffer, prompt->i);
	paste(prompt, buffer);
	copy(prompt, buffer, prompt->i);
}

void			termcap(t_ult *ult)
{
	t_prompt	*prompt;
	char		buffer[4];
	int			ret;

	prompt = init_prompt();
	stock_prompt(prompt, 0);
	stock_ult(ult, 0);
	prompt_print(prompt, 1);
	main_signal_handler();
	while ((ret = read(0, buffer, 4)) != -1)
	{
		prompt_shell(prompt, buffer, ult);
		if (buffer[0] == 4 && !prompt->cmd[0])
			exit_eof(ult->term, prompt);
		if (buffer[0] == 10 && buffer[1] == 0)
		{
			prompt_print(prompt, 0);
			fill_hist(&(ult->hist), prompt->cmd);
			!is_cmd_empty(prompt->cmd) ? ult->cmd = copy_cmd(prompt->cmd)
			: NULL;
			break ;
		}
		ft_bzero(buffer, 4);
	}
	free_prompt(&prompt);
}
