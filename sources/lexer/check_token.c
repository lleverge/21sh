/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 16:45:30 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/21 17:26:31 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static void		ft_error(char *error)
{
	ft_putendl_fd(error, 2);
}

int				check_pipe(char *str, int i)
{
	if (str[i + 1])
	{
		if (ft_istoken(str[i + 1]) && str[i + 1] != '|')
		{
			ft_error("error: parse error near '|'");
			return (-1);
		}
		else if (str[i + 2] && ft_istoken(str[i + 2]))
		{
			ft_error("error: parse error near '|'");
			return (-1);
		}
		else if (str[i + 1] == '|')
			return (OR);
		else if (str[i + 1] != '|')
			return (PIPE);
	}
	return (0);
}

int				check_and(char *str, int i)
{
	if (str[i - 1] != '&' && !ft_istoken(str[i + 1]) && str[i + 1] != '-')
	{
		ft_error("error: & not accepted");
		return (-1);
	}
	else if (ft_istoken(str[i + 1]) == 3)
	{
		ft_error("error: &| unknown");
		return (-1);
	}
	else if (ft_istoken(str[i + 1]) && str[i + 2] && ft_istoken(str[i + 2]))
	{
		ft_error("error: operator unknown");
		return (-1);
	}
	else if (str[i + 1] == '&')
		return (AND);
	else if (str[i + 1] == '>')
		return (AGGREG);
	else if (str[i + 1] == '<')
		return (AGGREG);
	return (0);
}

int				check_less(char *str, int i)
{
	if (str[i + 1])
	{
		if (!ft_istoken(str[i + 1]))
			return (LESS);
		else if (ft_istoken(str[i + 1]) && str[i + 2] && ft_istoken(str[i + 2]))
		{
			ft_error("error: operator unknown");
			return (-1);
		}
		else if (ft_istoken(str[i + 1]) && ft_istoken(str[i + 1]) != 1
				&& ft_istoken(str[i + 1]) != 4)
		{
			ft_error("error: operator unknown");
			return (-1);
		}
		else if (str[i + 1] == '<')
			return (DLESS);
		else if (str[i + 1] == '&')
			return (AGGREG);
	}
	return (0);
}

int				check_great(char *str, int i)
{
	if (str[i + 1])
	{
		if (!ft_istoken(str[i + 1]))
			return (GREAT);
		else if (ft_istoken(str[i + 1]) && str[i + 2] && ft_istoken(str[i + 2]))
		{
			ft_error("error: operator unknown");
			return (-1);
		}
		else if (ft_istoken(str[i + 1]) && ft_istoken(str[i + 1]) != 2
				&& ft_istoken(str[i + 1]) != 4)
		{
			ft_error("error: operator unknown");
			return (-1);
		}
		else if (str[i + 1] == '>')
			return (DLESS);
		else if (str[i + 1] == '&')
			return (AGGREG);
	}
	return (0);
}
