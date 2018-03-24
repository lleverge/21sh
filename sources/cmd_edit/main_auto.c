/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_auto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:32:19 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/24 17:08:22 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>


static t_compl	*init_coml_one(char *cmd)
{
	t_compl		*dest;

	dest = NULL;
	if (!(dest = (t_compl *)malloc(sizeof(t_compl))))
	{
		ft_putendl_fd("21sh : malloc error, abort.", 2);
		exit(3);
	}
	dest->name = ft_strdup(cmd);
	dest->next = NULL;
	dest->prev = NULL;
	return (dest);
}

t_compl	*basic_compl(void)
{
	t_compl *new;

	new = init_coml_one("DUMMY");
	new->prev = new;
	new->next = new;
	return (new);
}

void	read_compl(t_compl *list)
{
	char 	buffer[4];
	int		ret;

	ft_bzero(buffer, 4);
	while((ret = read(0, buffer, 4)) != -1)
	{
		if (T_LEFT)
			select_prev(list);
		if (T_RIGHT)
			select_next(list);
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
		list = basic_compl();
	list->cursored = 1;
	print_options(list);
	term_setup(ult, 1);
	read_compl(list);
	term_setup(ult, 0);
}
