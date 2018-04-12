/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:59:00 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/12 16:03:39 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

void		fork_error(char **cmd, char **path_tab)
{
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found.\n", 2);
	free_tab(path_tab);
}
