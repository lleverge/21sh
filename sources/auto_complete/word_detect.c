/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:31:43 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 15:48:28 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

char			*word_detect(t_prompt *prompt)
{
	int			index;
	int			start;

	index = prompt->i;
	if (ft_isspace(prompt->cmd[index]) && index > 0)
		index--;
	if (ft_isspace(prompt->cmd[index]))
		return (ft_strdup(""));
	while (index > 0)
	{
		if (ft_isspace(prompt->cmd[index - 1]))
			break ;
		index--;
	}
	start = index;
	index = prompt->i;
	while (index <= 1999 && (prompt->cmd[index] > 32 &&
	prompt->cmd[index] < 127))
		index++;
	return (ft_strsub(prompt->cmd, start, index - start));
}

static int		space_check(int i, char prompt[2000])
{
	int			index;

	index = i;
	while (index > 0)
	{
		if (!ft_isspace(prompt[index]))
			return (0);
		index--;
	}
	if (!ft_isspace(prompt[index]))
		return (0);
	return (1);
}

int				empty_space(t_prompt *prompt)
{
	int			index;

	index = 0;
	while (index < prompt->i)
	{
		if (!ft_isspace(prompt->cmd[index]))
			return (0);
		index++;
	}
	return (1);
}

int				first_word(t_prompt *prompt)
{
	char		*word;
	int			index;

	index = prompt->i;
	word = word_detect(prompt);
	if (!ft_strlen(word))
	{
		ft_strdel(&word);
		return (0);
	}
	if ((ft_isspace(prompt->cmd[index]) || prompt->cmd[index] == 0) &&
	index > 0)
		index--;
	while (index > 0 && !ft_isspace(prompt->cmd[index]))
		index--;
	ft_strdel(&word);
	if (index == 0 || space_check(index, prompt->cmd))
		return (1);
	return (0);
}
