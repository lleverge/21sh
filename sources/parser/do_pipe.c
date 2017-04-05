/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:14:10 by lleverge          #+#    #+#             */
/*   Updated: 2017/04/05 20:22:14 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

int		fork_pipe(t_ult *ult, char *cmd1, char *cmd2)
{
	char	**tab1;
	char	**tab2;
//	char	*cmd_path1;
//	char	*cmd_path2;
	char	**env_cpy;
	int		fd[2];
	pid_t	pid;

	
    tab1 = (char **)malloc(sizeof(char *) * 2);
    tab1[0] = strdup(cmd1);
    tab1[1] = 0;
    tab2 = (char **)malloc(sizeof(char *) * 3);
    tab2[0] = strdup(cmd2);
    tab2[1] = 0;
//	cmd_path1 = search_path(ult->path, tab1);
//	cmd_path2 = search_path(ult->path, tab2);
	env_cpy = list_in_tab(ult->env);
	if (pipe(fd) == -1)
	{
		ft_putendl_fd("pipe", 2);
		exit(-1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("fork", 2);
		exit(-1);
	}
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execve("/usr/bin/wc", tab1, env_cpy);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execve("/bin/ls", tab2, env_cpy);
	}
	return (0);
}

int			do_pipe(t_ult *ult, t_lexer *list)
{
	char	*cmd1;
	char	*cmd2;

	while (list->next)
	{
		if (list->token_id == 0)
		{
			cmd1 = ft_strdup(list->prev->content);
			cmd2 = ft_strdup(list->next->content);
			fork_pipe(ult, cmd1, cmd2);
		}
		list = list->next;
	}
	return (0);
}
