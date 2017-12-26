/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/26 14:20:48 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

int						check_aggreg(char *str, int i)
{
	int		j;
	int		fdi1;
	int		fdi2;
	char	*fd2;
	char	*fd1;

	j = i - 1;
	while (ft_isdigit(str[j]))
		j--;
	fd1 = ft_strsub(str, j + 1, i - j - 1);
	fdi1 = ft_atoi(fd1);
	j = i + 2;
	while (ft_isdigit(str[j]))
		j++;
	fd2 = ft_strsub(str, i + 2, j - i);
	fdi2 = ft_atoi(fd2);
	return (0);
}

char					*ft_strnosp(char *str)
{
	int		count;
	int		strlen;
	int		i;
	int		j;
	char	*nosp;

	count = 0;
	strlen = ft_strlen(str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			count++;
		i++;
	}
	if (!(nosp = (char *)malloc(sizeof(char) * (strlen - count))))
	{
		ft_putendl_fd("21sh: ft_strnosp malloc failed", 2);
		exit(-1);
	}
	while (*str)
	{
		if (!ft_isspace(*str))
		{
			nosp[j] = *str;
			j++;
		}
		str++;
	}
	return (nosp);
}

static int			builtin_launch(t_ult *ult, t_process *proc)
{
	int fd[3];
	int ret;

	fd[0] = dup(ult->fd[0]);
	fd[1] = dup(ult->fd[1]);
	fd[2] = dup(ult->fd[2]);
	if (set_fd_exec(proc) == -1)
		return (1);
	ret = search_for_builtins(ult, proc);
	close_fd_exec(proc);
	restore_fd(fd);
	return (ret);
}

int					seek_and_exec(t_ult *ult, t_job *job, char **cmd_tab)
{

	char	**cmd_tab2;

	cmd_tab2 = cmd_tab;
	if (check_for_builtin(*cmd_tab))
		return (builtin_launch(ult, job->proc));
	if (hash_search(*cmd_tab, ult->hash_table))
		return (exe_fork(ult->env, job->proc, ult));
	if (ft_strchr(*cmd_tab, '/') && !path_access_checker(*cmd_tab))
		return (exe_fork2(ult->env, job->proc, *cmd_tab));
	if (!ft_strchr(*cmd_tab, '/'))
	{
		ft_putstr_fd("21sh : command not found: ", 2);
		ft_putendl_fd(*cmd_tab, 2);
	}
	return (127);
}

int					start_prog(t_ult *ult, char **cmd)
{
	int		i;
	t_job	*job_li;
	t_job	*new;
	char	**cmd_tab;

	i = 0;
	job_li = NULL;
	cmd_tab = ft_strsplit_ws(cmd[0]);
	while (cmd[i])
	{
		new = create_job_node(cmd[i]);
		job_pushb(&job_li, new);
		job_li->proc = main_redirection_checker(job_li->proc, ult);
		i++;
	}
	ult->ret = seek_and_exec(ult, job_li, cmd_tab);
	free_tab(cmd_tab);
	destroy_job_list(job_li);
	return (0);
}
