/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 16:21:17 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/24 16:22:59 by vfrolich         ###   ########.fr       */
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