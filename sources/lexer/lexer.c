/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/24 14:17:51 by lleverge         ###   ########.fr       */
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

int								check_linker(t_job **job_li, char *cmd, int i)
{
	int		j;
	t_job	*new;
	char	*subcmd;

	j = i;
	new = NULL;
	while (cmd[j])
	{
		if (cmd[j] == '&' && cmd[j + 1] && cmd[j + 1] == '&')
		{
			subcmd = ft_strsub(cmd, i, j - i);
			new = create_job_node(subcmd, ft_strnosp(subcmd));
			new->linker = AND;
			job_pushb(job_li, new);
			return (j + 2);
		}
		else if (cmd[j] == '|' && cmd[j + 1] && cmd[j + 1] == '|')
		{
			subcmd = ft_strsub(cmd, i, j - i);
			new = create_job_node(subcmd, ft_strnosp(subcmd));
			new->linker = OR;
			job_pushb(job_li, new);
			return (j + 2);
		}
		else
			j++;
	}
	subcmd = ft_strsub(cmd, i, j - i);
	new = create_job_node(subcmd, ft_strnosp(subcmd));
	new->linker = SEPARATOR;
	job_pushb(job_li, new);
	return (j);
}

t_process						*new_lexer(char *str, t_process *proc_list)
{
	int				i;
	t_process		*new;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (ft_istoken(str[i]))
		{
			new = create_proc_node(new, str);
			if (ft_istoken(str[i]) == 1)
				new = check_less(str, i, new);
			else if (ft_istoken(str[i]) == 2)
				new = check_great(str, i, new);
			else if (ft_istoken(str[i]) == 3)
				new = check_pipe(str, i, new);
			else if (ft_istoken(str[i]) == 4)
				new = check_and(str, i, new);
			if (new == NULL)
				return (NULL);
			else
				proc_pushb(&proc_list, new);
		}
		i++;
	}
	if (new == NULL)
	{
		new = create_proc_node(new, str);
		proc_pushb(&proc_list, new);
	}
	return (proc_list);
}

int								start_prog(char *cmd, t_job **job_li)
{
	int		i;

	i = 0;
	while (cmd[i])
		i = check_linker(job_li, cmd, i);
	while (*job_li)
	{
		ft_putendl("Maillon job:");
		ft_putendl((*job_li)->cmd);
		(*job_li)->proc = new_lexer((*job_li)->cmd, (*job_li)->proc);
		while ((*job_li)->proc)
		{
			ft_putendl("Maillon proc:");
			ft_putendl((*job_li)->proc->cmd);
			ft_putstr("token_id = ");
			ft_putnbr((*job_li)->proc->token_id);
			ft_putchar('\n');
			(*job_li)->proc = (*job_li)->proc->next;
		}
		*job_li = (*job_li)->next;
	}
	return (0);
}
