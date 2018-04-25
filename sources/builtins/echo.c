/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:02:23 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/23 21:19:12 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		ft_echo(char **str)
{
	if (*str && !ft_strcmp(*str, "-n"))
	{
		str++;
		while (*str)
		{
			ft_putstr(*str);
			str++;
		}
		return (0);
	}
	if (*str && !ft_strncmp(*str, "-n", 2) && ft_strlen(*str) > 2)
	{
		ft_putendl_fd("usage: echo [-n] [string]", 2);
		return (1);
	}
	while (*str)
	{
		ft_putstr(*str);
		str++;
	}
	ft_putchar('\n');
	return (0);
}
