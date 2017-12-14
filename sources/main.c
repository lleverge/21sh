/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/14 21:01:44 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>
#include <cmd_edit.h>


 // static int		parse_error(char *cmd)
 // {
 // 	int		i;

 // 	i = 0;
 // 	while (ft_isspace(cmd[i]))
 // 		i++;
 // 	if (ft_istoken(cmd[i]) > 0)
 // 	{
 // 		ft_putstr_fd("21sh: parse error near ", 2);
 // 		ft_putchar_fd(cmd[i], 2);
 // 		ft_putchar_fd('\n', 2);
 // 		return (-1);
 // 	}
 // 	return (0);
 // }

 // static int		full_parse_error(char **cmd)
 // {
 // 	int		i;

 // 	i = 0;
 // 	while (cmd[i])
 // 	{
 // 		if (parse_error(cmd[i]) == -1)
 // 			return (-1);
 // 		i++;
 // 	}
 // 	return (0);
 // }

static	void	print_hash(t_hashelem **path_tab)
{
	t_hashelem	*tmp_list;
	int			i;

	i = 0;
	if (!path_tab)
		return ;
	tmp_list = NULL;
	while (i < 1021)
	{
		tmp_list = path_tab[i];
		while (tmp_list)
		{
			ft_putendl(tmp_list->bin_name);
			tmp_list = tmp_list->next;
		}
		i++;
	}
}

int				init_all(char **environ)
{
	t_ult		*ult;
	// char		**cmd;
	int			i;

	ult = NULL;
	ult = init_ult(ult, environ);
	while (42)
	{
		i = 0;
		get_prompt(ult->env);
		termcap(ult);
		ft_putchar('\n');
		// cmd = ft_strsplit_tok(ult->cmd);
		if (ult->cmd)
		{
			ult->ret = search_for_builtins(ult);
			if (!ft_strcmp(ult->cmd, "hash") && ult->hash_table)
				print_hash(ult->hash_table);
		}
		ult->cmd ? ft_strdel(&ult->cmd) : NULL;
		// ft_putendl("BP2");
		// if (ult->cmd)	
		 // if (cmd[i])
		 // {
		 // 	if (full_parse_error(cmd) == 0)
			// 	start_prog(ult, cmd);
		 // }
	}
	return (0);
}

int				main(int ac, char **av, char **environ)
{
	av = NULL;
	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("error: 21sh requires no arguments", 2);
		exit(-1);
	}
	init_all(environ);
	return (0);
}
