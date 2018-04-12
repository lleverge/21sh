/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:11:24 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 16:02:25 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**ret stands for the last return state to return in case of exit without arg
*/

int		clean_exit(char **arg, int ret)
{
	int tmp;

	if (arg[1] && arg[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (-1);
	}
	if (arg[1])
	{
		if (ft_strlen(arg[1]) && ft_isnumber(arg[1]))
		{
			tmp = ft_atoi(arg[1]);
			return (tmp);
		}
		ft_putendl_fd("exit: numeric argument required", 2);
		exit(0);
	}
	return (ret);
}
