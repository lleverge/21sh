/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_detect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 16:21:26 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 15:58:19 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		is_simple_redir(char *cmd)
{
	int i;

	i = 0;
	if (!cmd[i + 1])
		return (0);
	while (cmd[i])
	{
		if (cmd[i] && cmd[i + 1] && cmd[i] == '>')
		{
			if (cmd[i + 1] != '&' && cmd[i + 1] != '>')
			{
				if (i > 0)
				{
					if (cmd[i - 1] != '>' && !is_quoted(cmd, i))
						return (1);
				}
				else if (!is_quoted(cmd, i))
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int		is_fildes_agreg(char *cmd)
{
	int i;

	i = 0;
	if (!cmd[i + 1])
		return (0);
	while (cmd[i])
	{
		if (cmd[i + 1] && cmd[i] == '>')
		{
			if (cmd[i + 1] == '&' && !is_quoted(cmd, i) &&
				!is_quoted(cmd, i + 1))
				return (1);
		}
		i++;
	}
	return (0);
}

int		is_input_redir(char *cmd)
{
	int i;

	i = 0;
	if (!cmd[i + 1])
		return (0);
	while (cmd[i])
	{
		if (cmd[i] && cmd[i + 1] && cmd[i] == '<')
		{
			if (cmd[i + 1] != '<')
			{
				if (i > 0)
				{
					if (cmd[i - 1] != '<' && !is_quoted(cmd, i))
						return (1);
				}
				else if (!is_quoted(cmd, i))
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int		is_redir_append(char *cmd)
{
	int i;

	i = 0;
	if (!cmd[i + 1])
		return (0);
	while (cmd[i])
	{
		if (cmd[i + 1] && cmd[i] == '>')
		{
			if (cmd[i + 1] == '>' && !is_quoted(cmd, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int		is_heredoc(char *cmd)
{
	int i;

	i = 0;
	if (!cmd[i + 1])
		return (0);
	while (cmd[i])
	{
		if (cmd[i + 1] && cmd[i] == '<')
		{
			if (cmd[i + 1] == '<' && !is_quoted(cmd, i))
				return (1);
		}
		i++;
	}
	return (0);
}
