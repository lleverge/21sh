/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 14:25:18 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/25 14:28:17 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

void			ft_env_error(char *file)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int                 env_manage_error(char *cmd)
{
	t_stat  st;

	if (stat(cmd, &st) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory.\n", 2);
		return (-1);
	}
	else if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied.\n", 2);
		return (-1);
	}
	return (0);
}
