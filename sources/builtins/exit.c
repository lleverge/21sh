/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:11:24 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/29 14:11:52 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**ret stands for the last return state to return in case of exit without arg
*/

int		clean_exit(char **arg, int ret)
{
	int		tmp;
	t_ult	*ult;

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
		ult = NULL;
		ult = stock_ult(ult, 1);
		reset_term(ult->term);
		exit(255);
	}
	return (ret);
}
