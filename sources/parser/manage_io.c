/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:37:18 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/24 19:15:27 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

static int		get_fds_output(t_ult *ult, t_parser *process, int i, char *str)
{
	int len;

	len = fd_len(str, i);
	if (!i && len == 1)
		process->stdout = ft_atoi(&str[i]);
	else if (len == 1 && (ft_atoi(&str[i]) >= 0 && ft_atoi(&str[i]) <= 2))
		ult->exec->fd_write = ft_atoi(&str[i]);
	else
	{
		process->shutout_out = 1;
		ft_putendl_fd("42sh: bad file descriptor.", 2);
		return (-1);
	}
	return (0);
}

static int		io_file_output(t_ult *ult, t_parser *process,
							t_lexer *list_lex, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			if (get_fds_output(ult, process, i, str) == -1)
				return (-1);
		}
		if (str[i] == '-')
			process->shutout_out = 1;
		i++;
	}
	if (list_lex->next && process->token != LESS)
		open_redir(ult, list_lex);
	return (0);
}

static int		get_fds_input(t_ult *ult, t_parser *process, int i, char *str)
{
	int len;

	len = fd_len(str, i);
	if (!i && len == 1 && (ft_atoi(&str[i]) >= 0 && ft_atoi(&str[i]) <= 9))
		process->stdin = ft_atoi(&str[i]);
	else if (len == 1 && (ft_atoi(&str[i]) >= 0 && ft_atoi(&str[i]) <= 2))
	{
		process->stdin = 0;
		ult->exec->fd_write = ft_atoi(&str[i]);
	}
	else
	{
		ft_putendl_fd("42sh: bad file descriptor.", 2);
		return (-1);
	}
	return (0);
}

static int		io_file_input(t_ult *ult, t_parser *process, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			if (get_fds_input(ult, process, i, str) == -1)
				return (-1);
		}
		if (str[i] == '-')
			process->shutout_in = 1;
		i++;
	}
	return (0);
}

int				manage_io_files(t_ult *ult, t_lexer *list, t_parser *process, int token)
{
	if (token == GREAT || token == DGREAT)
	{
		while (process->next)
			process = process->next;
		if (io_file_output(ult, process, list, list->content) == -1)
			return (-1);
	}
	else if (token == LESS || token == DLESS)
	{
		while (process->next)
		{
			if (process->token == LESS || process->token == DLESS)
			{
				ft_putendl_fd("42sh: Ambiguous input redirect.", 2);
				return (-2);
			}
			process = process->next;
		}
		if (io_file_input(ult, process, list->content) == -1)
			return (-2);
	}
	return (0);
}
