/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:06:52 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/27 13:27:17 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

static int	*singlet_signal(int *flag, int mode)
{
	static int *value;

	if (!mode)
		value = flag;
	else
		flag = value;
	return (value);
}

static void	small_handler(int signal)
{
	int *flag;

	if (signal != SIGINT)
		return ;
	flag = NULL;
	flag = singlet_signal(flag, 1);
	*flag = 0;
}

int prompt_for_display(t_compl *list)
{
	char	buffer[4];
	int		flag;

	flag = 1;
	singlet_signal(&flag, 0);
	signal(SIGINT, &small_handler);
	ft_putstr("Display all ");
	ft_putnbr(count_entries(list));
	ft_putstr(" possibilities? (y or n)");
	tputs(tgetstr("vs", NULL), 1 , ft_putchar_int);
	ft_bzero(&buffer, 4);
	while (read(0, buffer, 4) != -1 && flag)
	{
		if (*buffer == 'y' || *buffer == 'Y')
		{
			tputs(tgetstr("vi", NULL), 1 , ft_putchar_int);
			return (0);
		}
		if (*buffer == 'n' || *buffer == 'N')
			flag = 0;
		ft_bzero(&buffer, 4);
	}
	tputs(tgetstr("vi", NULL), 1 , ft_putchar_int);
	return (1);
}

int	ask_prompt(t_compl *list)
{
	size_t	lines_needed;

	lines_needed = count_lines(list);
	if (lines_needed >= get_term_size("row")
		&& !prompt_for_display(list))
	{
		ft_putchar('\n');
		main_signal_handler();
		return (1);
	}
	ft_putchar('\n');
	main_signal_handler();
	return (0);
}