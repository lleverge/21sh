/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/11/23 20:21:45 by vfrolich         ###   ########.fr       */
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

// char	*get_pathstring(void)
// {
// 	char	*path_string;

// 	path_string = NULL;
// 	if (!(path_string = getenv("PATH")))
// 		ft_putendl("pathstring NULL");
// 	path_string ? ft_putendl(path_string) : ft_putendl("pathstring NULL");
// 	return (path_string);
// }

// int		basic_hash(char *entry)
// {
// 	char	*path_word;
// 	char	*tmp;
// 	int		hash_ret;

// 	if (!(path_word = get_pathstring()))
// 	{	
// 		ft_putendl("unable to get pathstring");
// 		return (-1);
// 	}
// 	if (path_word)
// 		tmp = entry;
// 	else 
// 		tmp = path_word;
// 	hash_ret = 0;
// 	while (*tmp)
// 	{
// 		hash_ret += *tmp;
// 		tmp++;
// 	}
// 	return (hash_ret%546);
// }

int				init_all(char **environ)
{
	t_ult		*ult;
	// char		**cmd;
	t_job		*job_li;
	int			i;

	ult = NULL;
	job_li = NULL;
	ult = init_ult(ult, environ);
	hash_init();
	exit (0);
	while (42)
	{
		i = 0;
		get_prompt(ult->env);
		termcap(ult);
		ft_putchar('\n');
		// if (cmd[i])
		// {
		// 	if (full_parse_error(cmd) == 0)
		// 	{
		// 		while (cmd[i])
		// 		{
		// 			start_prog(cmd[i], &job_li);
		// 			i++;
		// 		}
		// 	}
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
