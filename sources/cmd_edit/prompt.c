/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 14:15:33 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/15 15:56:22 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "cmd_edit.h"

static void		color(char *str, char *col)
{
	ft_putstr("\e");
	ft_putstr(col);
	ft_putstr(str);
	ft_putstr("\033[0m");
}

static void		put_home(char *home, char *cwd)
{
	color("~", CYAN);
	color((ft_strstr(cwd, home) + ft_strlen(home)), CYAN);
}

static int		prompt_handle(char *user, int i)
{
	if (user)
	{
		i = ft_strlen(user) + 1;
		color(user, YELLOW);
		ft_putchar(' ');
	}
	else
	{
		color("incognito ", RED);
		i = 10;
	}
	return (i);
}

static int		put_prompt(char *user, char *home, char *pwd)
{
	int i;

	i = 5;
	i = prompt_handle(user, i);
	if (pwd && home && ft_strstr(pwd, home))
	{
		i += ft_strlen(ft_strstr(pwd, home) + ft_strlen(home)) + 1;
		put_home(home, pwd);
		ft_strdel(&pwd);
	}
	else if (pwd && pwd[0])
	{
		i += ft_strlen(pwd);
		color(pwd, CYAN);
		ft_strdel(&pwd);
	}
	else
	{
		i += 7;
		color("nowhere", RED);
	}
	ft_putstr(" $> ");
	ft_strdel(&user);
	ft_strdel(&home);
	return (i);
}

int				prompt(t_edit *ed)
{
	char			*user;
	char			*home;
	char			*pwd;
	int				i;

	user = get_node_content(ed->env, "USER");
	home = get_node_content(ed->env, "HOME");
	pwd = get_node_content(ed->env, "PWD");
	i = put_prompt(user, home, pwd);
	ed->input->lprom = i + 3;
	ed->input->curs->x = i + 4;
	return (i);
}
