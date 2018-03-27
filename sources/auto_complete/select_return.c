/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_return.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 17:40:52 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/27 12:17:29 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void			select_in_prompt(char *select, char *cmd, int index)
{
	char	*tmp;
	char	*result;
	size_t		i;
	
	i = 0;
	tmp = ft_strdup(cmd + index + 1);
	ft_memmove(cmd + index + 1, select, ft_strlen(select));
	result = ft_strcat(cmd, tmp);
	while (i < ft_strlen(result))
	{
		cmd[i] = result[i];
		i++;
	}
	ft_strdel(&tmp);
}
