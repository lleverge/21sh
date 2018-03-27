/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_auto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:32:19 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/27 16:53:24 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

void	read_compl(t_compl *list, t_prompt *prompt)
{
	char 	buffer[4];
	int		ret;

	ft_bzero(buffer, 4);
	print_options(list);
	while((ret = read(0, buffer, 4)) != -1)
	{
		clr_screen(list);
		if (T_LEFT)
			select_prev(list);
		if (T_RIGHT)
			select_next(list);
		if (T_TAB)
		{
			do_selection(list, prompt);
			return ;
		}
		print_options(list);
		ft_bzero(buffer, 4);
	}
}

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
	if (first_word(prompt) || empty_space(prompt))
		list = init_cmd_compl(ult, word);
	else
	{
		// list = basic_compl();
		return ;
	}
	if (!list)
		return ;
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
	term_setup(ult, 1);
	read_compl(list, prompt);
	ft_putendl("BPPPPPPPP");
	get_prompt(ult->env);
	prompt_print(prompt, 1);
	free(ult->term);
	ult->term = init_term();
	free_all_choices(list);
	ft_putendl("after main_auto");
}
