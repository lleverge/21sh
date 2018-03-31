/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_return.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 17:40:52 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/31 13:45:42 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

static int		detect_index(t_prompt *prompt)
{
	int			index;

	index = prompt->i;
	if (ft_isspace(prompt->cmd[index]) && index > 0 &&
		ft_isspace(prompt->cmd[index - 1]))
		return (index);
	while (index > 0)
	{
		if (ft_isspace(prompt->cmd[index - 1]))
			break ;
		index--;
	}
	return (index);
}

static int		detect_index_end(t_prompt *prompt)
{
	int			index;

	index = prompt->i;
	if (ft_isspace(prompt->cmd[index]))
		return (index);
	while (index < 1999)
	{
		if (ft_isspace(prompt->cmd[index]) || !prompt->cmd[index])
			break ;
		index++;
	}
	return (index);
}

static void		gather(char *before, char *select, char *after, t_prompt *p)
{
	int			index;

	index = 0;
	if (before)
		ft_strcpy(p->cmd, before);
	if (before)
		index += ft_strlen(before);
	ft_strcpy(&p->cmd[index], select);
	index += ft_strlen(select);
	if (after)
		ft_strcpy(&p->cmd[index], after);
	p->i = index;
}

void			select_in_prompt(char *select, t_prompt *prompt)
{
	char		*before;
	char		*after;

	if ((detect_index_end(prompt) + 1) >= 1999)
		return ;
	after = NULL;
	after = ft_strdup(&(prompt->cmd[detect_index_end(prompt)]));
	if (!detect_index(prompt))
		before = NULL;
	else
		before = ft_strsub(prompt->cmd, 0, detect_index(prompt));
	gather(before, select, after, prompt);
	before ? ft_strdel(&before) : NULL;
	after ? ft_strdel(&after) : NULL;
}
