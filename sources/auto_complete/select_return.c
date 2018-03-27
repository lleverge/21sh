/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_return.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 17:40:52 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/27 16:57:18 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

static int		detect_index(t_prompt *prompt)
{
	int		index;

	index = prompt->i;
	if (ft_isspace(prompt->cmd[index]))
		return (index);
	while (index > 0)
	{
		if (ft_isspace(prompt->cmd[index - 1]))
			break ;
		index--;
	}
	return (index);
}

void			select_in_prompt(char *select, t_prompt *prompt)
{
	char	*tmp;
	char	*word;
	char	*tmp2;
	size_t		i;
	
	i = 0;
	word = word_detect(prompt);
	tmp2 = &prompt->cmd[detect_index(prompt)];
	tmp = ft_strdup(prompt->cmd + prompt->i);
	ft_memmove(tmp2, select, ft_strlen(select));
	ft_strdel(&word);
	word = ft_strcat(prompt->cmd, tmp);
	while (i < ft_strlen(word))
	{
		prompt->cmd[i] = word[i];
		i++;
	}
	ft_strdel(&tmp);
	ft_strdel(&word);
}
