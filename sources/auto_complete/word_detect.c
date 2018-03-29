/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:31:43 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/29 13:39:05 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

char	*word_detect(t_prompt *prompt)
{
	int		index;
	int		start;

	index = prompt->i;
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
	while (index <= 1999 && (prompt->cmd[index] > 32 && prompt->cmd[index] < 127))
		index++;
	return (ft_strsub(prompt->cmd, start, index - start));
}

static int		space_check(t_prompt *prompt)
{
	int		index;

	index = prompt->i;
	while (index > 0 && (prompt->cmd[index] > 32 && prompt->cmd[index] < 127))
		index--;
	while (index >= 0)
	{
		if (prompt->cmd[index] > 32 && prompt->cmd[index] < 127)
			return (0);
		index--;
	}
	return (1);
}

int				empty_space(t_prompt *prompt)
{
	int 	index;

	index = prompt->i;
	while (index > 0 && ft_isspace(prompt->cmd[index]))
		index--;
	return (!index ? 1 : 0);
}

int		first_word(t_prompt	*prompt)
{
	char	*word;
	char	*pos;
	int		index;

	index = prompt->i;
	word = word_detect(prompt);
	if (!ft_strlen(word))
	{
		ft_strdel(&word);
		return (0);
	}
	while (index > 0 && prompt->cmd[index])
	{
		if (ft_isspace(prompt->cmd[index - 1]))
			break;
		index--;
	}
	pos = &prompt->cmd[index];
	ft_strdel(&word);
	if (pos == prompt->cmd || space_check(prompt))
		return (1);
	return (0);
}