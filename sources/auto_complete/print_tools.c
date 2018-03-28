/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 16:21:17 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/28 22:12:16 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

size_t				get_term_size(char *field)
{
	struct winsize	win;

	ft_bzero(&win, sizeof(win));
	if (ioctl(STDIN_FILENO, TIOCGSIZE, &win) == -1)
	{
		write(STDERR_FILENO, "ft_select: unable to get terminal size\n",
			sizeof("ft_select: unable to get terminal size\n"));
		return (0);
	}
	if (!ft_strcmp(field, "row"))
		return (win.ws_row);
	return (win.ws_col);
}

size_t	get_largest_word(t_compl *list)
{
	size_t 	res;
	t_compl *tmp;

	res = ft_strlen(list->name);
	tmp = list->next;
	while (tmp != list)
	{
		if (ft_strlen(tmp->name) > res)
			res = ft_strlen(tmp->name);
		tmp = tmp->next;
	}
	return (res);
}

size_t	word_per_line(t_compl *list)
{
	size_t 	largest;
	size_t	term_co;

	largest = get_largest_word(list);
	term_co = get_term_size("col");
	return (term_co/(largest + 1));
}

size_t	count_entries(t_compl *list)
{
	size_t count;
	t_compl *tmp;

	count = 1;
	tmp = list;
	tmp = tmp->next;
	while (tmp != list)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

size_t 	count_lines(t_compl *list)
{
	size_t 	wpl;
	size_t	nb_entries;
	size_t lines_needed;

	wpl = word_per_line(list);
	nb_entries = count_entries(list);
	if (nb_entries < wpl)
		return (1);
	lines_needed = nb_entries/wpl;
	if (nb_entries%wpl)
		lines_needed++;
	return (lines_needed);
}

void	clr_screen(t_compl *list)
{
	size_t nb_entries;
	size_t lines_needed; 

	nb_entries = count_entries(list);
	lines_needed = count_lines(list);
	while (lines_needed > 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
		lines_needed--;
	}
	tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
}
