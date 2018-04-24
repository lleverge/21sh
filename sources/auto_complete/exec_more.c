/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 17:30:03 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/24 17:10:43 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

static void	write_it(char *field, size_t padd_size, int fd)
{
	int	to_print;
	
	to_print = padd_size - ft_strlen(field);
	ft_putstr_fd(field, fd);
	while (to_print >= 0)
	{
		ft_putchar_fd(' ', fd);
		to_print--;
	}
}

static void	write_in_pipe(t_compl *list, int fd)
{
	size_t	largest;
	size_t	word_line;
	size_t	i;
	t_compl *tmp;

	largest = get_largest_word(list);
	word_line = word_per_line(list);
	tmp = list;
	write_it(tmp->name, largest, fd);
	tmp = tmp->next;
	i = 1;
	while (tmp != list)
	{
		while (i <= word_line && tmp != list)
		{
			write_it(tmp->name, largest, fd);
			i++;
			tmp = tmp->next;
		}
		ft_putchar_fd('\n', fd);
		i = 0;
	}
	close(fd);
}

static void io_block(int flag, int fd)
{
	int opt;

	opt = flag;
	ft_putnbrendl(opt);
	ioctl(fd, FIONBIO, &opt);
}

static void cleanup(int fd[2], char **env_dup, char **arg)
{
	close(fd[0]);
	free_tab(env_dup);
	free_tab(arg);
}

void		exec_more(t_compl *list, t_ult *ult)
{
	int		fd[2];
	pid_t	pid;
	char	**env_dup;
	char	**arg;

	if (pipe(fd) == -1)
		return ;
	io_block(1, fd[1]);
	write_in_pipe(list, fd[1]);
	io_block(0, fd[1]);
	env_dup = list_in_tab(ult->env);
	arg = (char **)malloc(sizeof(char *) * 2);
	arg[0] = ft_strdup("/usr/bin/more");
	arg[1] = NULL;
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		reset_term(ult->term);
		dup2(fd[0], 0);
		execve("/usr/bin/more", arg, env_dup);
	}
	else
		wait(NULL);
	cleanup(fd, env_dup, arg);
}
