/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_auto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:32:19 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/16 17:51:28 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"
#include "../../includes/shell.h"

static void		void_prompt(void)
{
	t_prompt	*prompt;
	t_ult		*ult;

	prompt = NULL;
	prompt = stock_prompt(prompt, 1);
	prompt_print(prompt, 0);
	ult = NULL;
	ult = stock_ult(ult, 1);
	term_setup(ult, 1);
	ft_putchar('\n');
}

static void		cleanup(t_prompt *prompt, t_ult *ult, t_compl *list)
{
	tputs(tgetstr("up", NULL), 1, ft_putchar_int);
	tputs(tgetstr("up", NULL), 1, ft_putchar_int);
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
	get_prompt(ult->env);
	prompt_print(prompt, 1);
	free_all_choices(list);
	free(ult->term);
	ult->term = init_term();
}

static void		simple_print(t_ult *ult, t_compl *list, t_prompt *prompt)
{
	term_setup(ult, 0);
	if (ask_prompt(list))
		exec_more(list, ult);
	cleanup(prompt, ult, list);
}

static void		main_auto2(t_prompt *prompt, t_compl *list, t_ult *ult)
{
	if (count_lines(list) >= get_term_size("row"))
		simple_print(ult, list, prompt);
	else
	{
		count_entries(list) > 1 ? read_compl(list, prompt) :
			do_selection(list, prompt);
		cleanup(prompt, ult, list);
	}
}

void			main_auto(t_prompt *prompt, char *buffer, t_ult *ult)
{
	char		*word;
	t_compl		*list;

	if (!T_TAB)
		return ;
	word = word_detect(prompt);
	list = NULL;
	if (empty_space(prompt) || first_word(prompt))
		list = init_cmd_compl(ult, word);
	else
		list = classic_compl(prompt);
	if (!list)
	{
		ft_strdel(&word);
		return ;
	}
	word ? ft_strdel(&word) : NULL;
	void_prompt();
	main_auto2(prompt, list, ult);
}
