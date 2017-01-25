/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/25 15:27:24 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			init_all(char **environ)
{
	t_ult	*ult;

	ult = NULL;
	ult = init_ult(ult, environ);
	prompt(ult->env);
	return (0);
}

int			main(int ac, char **av, char **environ)
{
	av = NULL;
	(void)av;
	if (ac != 1)
		ft_putendl_fd("error: 21sh requires no arguments", 2);
	init_all(environ);
	return (0);
}
