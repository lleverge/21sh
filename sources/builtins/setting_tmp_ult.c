/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_tmp_ult.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:59:41 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/22 19:21:28 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"
#include "../../includes/builtins.h"
#include "../../includes/cmd_edit.h"

static void	init_tmp_term(t_ult *ult, t_ult *dest)
{
	t_term	*termi;

	if (!(termi = (t_term *)malloc(sizeof(t_term))))
	{
		ft_putendl_fd("error: term struct malloc failed", 2);
		exit_term(ult->term);
		exit(3);	
	}
	termi->fd = ult->term->fd;
	termi->termios.c_lflag = ult->term->termios.c_lflag;
	termi->termios.c_cc[VMIN] = ult->term->termios.c_cc[VMIN];
	termi->termios.c_cc[VTIME] = ult->term->termios.c_cc[VTIME];
	dest->term = termi;
}

t_ult		*setting_tmp_ult(t_ult *ult, t_env *env)
{
	t_ult		*dest;

	dest = NULL;
	if (!(dest = (t_ult *)malloc(sizeof(t_ult))))
	{
		ft_putendl_fd("error: ult struct malloc failed", 2);
		exit_term(ult->term);
		exit(3);
	}
	dest->env = env;
	if (!env)
		dest->hash_table = NULL;
	else
		dest->hash_table = table_init(env);
	dest->fd[0] = ult->fd[0];
	dest->fd[1] = ult->fd[1];
	dest->fd[2] = ult->fd[2];
	dest->term = NULL;
	init_tmp_term(ult, dest);
	return (dest);
}
