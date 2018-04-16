/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 17:57:56 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/16 15:48:07 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"
#include <sys/stat.h>

static int		test_isdir(char *path)
{
	struct stat	*stats;
	t_ult		*ult;

	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!(stats = malloc(sizeof(struct stat))))
	{
		ft_putstr_fd("21sh : malloc error", 2);
		exit_term(ult->term);
		exit(3);
	}
	if (stat(path, stats) == -1)
	{
		ft_putstr_fd("21sh : malloc error", 2);
		stats ? free(stats) : NULL;
		return (1);
	}
	if ((!S_ISDIR(stats->st_mode)) && (!S_ISLNK(stats->st_mode)))
	{
		ft_putstr_fd("cd: Not a directory: ", 2);
		ft_putendl_fd(path, 2);
		free(stats);
		return (0);
	}
	free(stats);
	return (1);
}

int				check_for_access(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: No such directory: ", 2);
		ft_putendl_fd(path, 2);
		return (1);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("cd: Permission denied: ", 2);
		ft_putendl_fd(path, 2);
		return (1);
	}
	return (test_isdir(path) ? 0 : 1);
}
