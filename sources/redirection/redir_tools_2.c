/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 17:06:22 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/29 14:04:33 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

char	*fd_to_atoi(char *sub_cmd)
{
	int	i;

	i = 0;
	while (ft_isdigit(sub_cmd[i]))
		i++;
	return (ft_strsub(sub_cmd, 0, i));
}

int		is_validchar(char *cmd, int index)
{
	if (!cmd[index])
		return (0);
	if (is_quoted(cmd, index))
		return (1);
	if (cmd[index] == '>' || cmd[index] == '<' || ft_isspace(cmd[index]))
		return (0);
	return (1);
}
