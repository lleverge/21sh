/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/23 16:51:33 by lleverge         ###   ########.fr       */
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

	i = 0;
	job_li = NULL;
	while (cmd[i])
	{
		new = create_job_node(cmd[i]);
		job_pushb(&job_li, new);
		job_li->proc = main_redirection_checker(job_li->proc, ult);
		exe_fork(ult->env, job_li->proc, ult->hash_table);
		i++;
	}
	destroy_job_list(job_li);
	return (0);
}
