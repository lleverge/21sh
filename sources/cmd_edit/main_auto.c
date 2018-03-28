/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_auto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:32:19 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/28 19:59:14 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

void	term_setup(t_ult *ult, int value)
{
	ult->term->fd = open(ttyname(0), O_RDWR);
	if (tcgetattr(ult->term->fd, &(ult->term->termios)) == -1)
	{
		ft_putendl("error: tcgetattr");
		return ;
	}
	ult->term->termios.c_cc[VMIN] = value;
	if (tcsetattr(ult->term->fd, TCSANOW, &(ult->term->termios)) == -1)
	{
		ft_putendl_fd("error: tcsetattr", 2);
		return ;
	}
	close(ult->term->fd);
}

static void	void_prompt(void)
{
	t_prompt *prompt;

	prompt = NULL;
	prompt = stock_prompt(prompt, 1);
	prompt_print(prompt, 0);
	ft_putchar('\n');
}

void	main_auto(t_prompt *prompt, char *buffer, t_ult *ult)
{
	char *word;
	t_compl	*list;

	if (!T_TAB)
		return ;
	word = word_detect(prompt);
	list = NULL;
	if (first_word(prompt) || empty_space(prompt))
		list = init_cmd_compl(ult, word);
	else
	{
		ft_strdel(&word);
		return ;
	}
	if (!list)
	{
		ft_strdel(&word);
		return ;
	}
	ft_strdel(&word);
	void_prompt();
	if (count_lines(list) >= get_term_size("row"))
	{
		term_setup(ult, 0);
		if (ask_prompt(list))
			exec_more(list, ult);
		get_prompt(ult->env);
		prompt_print(prompt, 1);
		free_all_choices(list);
		free(ult->term);
		ult->term = init_term();
		return ;
	}
	read_compl(list, prompt);
	get_prompt(ult->env);
	prompt_print(prompt, 1);
	free_all_choices(list);
	free(ult->term);
	ult->term = init_term();
}
