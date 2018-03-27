/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_return.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 17:40:52 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/27 15:14:11 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void			select_in_prompt(char *select, t_prompt *prompt)
{
	char	*tmp;
	char	*word;
	char	*tmp2;
	char	*result;
	size_t		i;
	
	i = 0;
	word = word_detect(prompt);
	tmp2 = ft_strstr(word);
	tmp = ft_strdup(prompt->cmd + prompt->i + );
	ft_memmove(prompt->cmd + tmp2, select, ft_strlen(select));
	result = ft_strcat(prompt->cmd, tmp);
	while (i < ft_strlen(result))
	{
		prompt->cmd[i] = result[i];
		i++;
	}
	ft_strdel(&tmp);
	ft_strdel(word);
}
