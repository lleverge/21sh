/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_compl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 20:51:02 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 15:47:54 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

size_t		count_entries(t_compl *list)
{
	size_t	count;
	t_compl	*tmp;

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

static void	print_one(t_compl *list, size_t largest)
{
	int		to_print;

	if (list->cursored == 1)
	{
		tputs(tgetstr("mr", NULL), 1, ft_putchar_int);
		ft_putstr(list->name);
		tputs(tgetstr("me", NULL), 1, ft_putchar_int);
	}
	else
		ft_putstr(list->name);
	to_print = largest - ft_strlen(list->name);
	while (to_print >= 0)
	{
		ft_putchar(32);
		to_print--;
	}
}

void		print_options(t_compl *list)
{
	size_t	word_line;
	size_t	largest;
	size_t	i;
	t_compl	*tmp;

	word_line = word_per_line(list);
	tmp = list;
	largest = get_largest_word(list);
	print_one(tmp, largest);
	tmp = tmp->next;
	i = 1;
	while (tmp != list)
	{
		while (i < word_line && tmp != list)
		{
			print_one(tmp, largest);
			i++;
			tmp = tmp->next;
		}
		ft_putchar('\n');
		i = 0;
	}
}
