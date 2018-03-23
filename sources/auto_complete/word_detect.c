/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:31:43 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/23 17:25:33 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

char	*word_detect(t_prompt *prompt)
{
	int		index;
	int		start;

	index = prompt->i;
	while (index > 0 && (prompt->cmd[index] > 32 && prompt->cmd[index] < 127))
		index--;
	start = index;
	index = prompt->i;
	while (index <= 1999 && (prompt->cmd[index] > 32 && prompt->cmd[index] < 127))
		index++;
	return (ft_strsub(prompt->cmd, start, index - start));
}

// int		first_word(t_prompt	*prompt)
// {
	
// }