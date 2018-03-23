/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_auto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:32:19 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/23 21:29:10 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

// static void		print_completion(t_compl *list)
// {
// 	t_compl *choice;

// 	if (!list)
// 		return ;
// 	choice = list;
// 	ft_putendl(choice->name);
// 	while (choice->next != list)
// 	{
// 		choice = choice->next;
// 		ft_putendl(choice->name);
// 	}
// }

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
	// word_per_line(list);
	// print_completion(list);
}