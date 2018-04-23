/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cut_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:23:15 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/23 17:04:18 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void			quote_extracter(char *cmd, int *i)
{
	int		index;
	char	quote_char;

	index = *i;
	quote_char = cmd[index];
	index++;
	while (cmd[index] && cmd[index] != quote_char)
			index++;
	if (cmd[index])
		index++;
	*i = index;
}

int				get_wordlen(char *sub_cmd)
{
	int			index;
	char		quote_char;
	char		*tmp;

	index = 0;
	quote_char = *sub_cmd;
	tmp = sub_cmd;
	if (tmp[1])
		tmp++;
	while (tmp[index] && tmp[index] != quote_char)
		index++;
	return (index);
}
