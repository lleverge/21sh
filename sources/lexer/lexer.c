/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/24 12:27:47 by vfrolich         ###   ########.fr       */
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

int								start_prog(t_ult *ult, char **cmd)
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
	if (!check_for_builtin(cmd_tab[0]))
	{
		if (hash_search(cmd[0], ult->hash_table))
			exe_fork(ult->env, job_li->proc, ult->hash_table);
		else if (ft_strchr(cmd[0], '/'))
		{
			if (!path_access_checker(cmd[0]))
				exe_fork(ult->env, job_li->proc, ult->hash_table);
		}
	}
	free_tab(cmd_tab);
	destroy_job_list(job_li);
	return (0);
}
