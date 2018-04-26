/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:02:23 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/26 20:30:15 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int		no_nl(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		ft_putstr(arg[i]);
		i++;
		if (arg[i])
			ft_putchar(32);
	}
	return (0);
}

int				ft_echo(char **str)
{
	int		i;

	if (*str && !ft_strcmp(*str, "-n"))
	{
		str++;
		return (no_nl(str));
	}
	if (*str && !ft_strncmp(*str, "-n", 2) && ft_strlen(*str) > 2)
	{
		ft_putendl_fd("usage: echo [-n] [string]", 2);
		return (1);
	}
	i = 0;
	while (str[i])
	{
		ft_putstr(str[i]);
		i++;
		if (str[i])
			ft_putchar(32);
	}
	ft_putchar('\n');
	return (0);
}
