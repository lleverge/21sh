/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_blankword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:55:27 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/25 17:59:43 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			is_blankword(char *str)
{
	char	*tmp;

	if (!str)
		return (-1);
	tmp = str;
	while (*tmp)
	{
		if (!ft_isspace(*tmp))
			return (0);
		tmp++;
	}
	return (1);
}
