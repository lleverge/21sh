/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 16:45:30 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/26 10:25:02 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static void				ft_error(char *error)
{
	ft_putendl_fd(error, 2);
}

t_process				*check_pipe(char *str, int i, t_process *new)
{
	ft_strlen(new->cmd);
	if (str[i + 1])
	{
		if (ft_istoken(str[i + 1]) && str[i + 1] != '|')
		{
			ft_error("error: parse error near '|'");
			return (NULL);
		}
		else if (str[i + 2] && ft_istoken(str[i + 2]))
		{
			ft_error("error: parse error near '|'");
			return (NULL);
		}
		else if (str[i + 1] == '|')
			return (NULL); //OR
		else if (str[i + 1] != '|')
			return (NULL); //PIPE
	}
	return (NULL);
}

t_process				*check_and(char *str, int i, t_process *new)
{
	ft_strlen(new->cmd);
	if (str[i - 1] != '&' && !ft_istoken(str[i + 1]) && str[i + 1] != '-')
	{
		ft_error("error: & not accepted");
		return (NULL);
	}
	else if (ft_istoken(str[i + 1]) == 3)
	{
		ft_error("error: &| unknown");
		return (NULL);
	}
	else if (ft_istoken(str[i + 1]) && str[i + 2] && ft_istoken(str[i + 2]))
	{
		ft_error("error: operator unknown");
		return (NULL);
	}
	else if (str[i + 1] == '&')
		return (NULL); //AND
	else if (str[i + 1] == '>')
		return (NULL); // AGGREG
	else if (str[i + 1] == '<')
		return (NULL); //AGGREG
	return (NULL);
}

t_process				*check_less(char *str, int i, t_process *new)
{
	ft_strlen(new->cmd);
	if (str[i + 1])
	{
		if (!ft_istoken(str[i + 1]))
			return (NULL); //LESS
		else if (ft_istoken(str[i + 1]) && str[i + 2] && ft_istoken(str[i + 2]))
		{
			ft_error("error: operator unknown");
			return (NULL);
		}
		else if (ft_istoken(str[i + 1]) && ft_istoken(str[i + 1]) != 1
				&& ft_istoken(str[i + 1]) != 4)
		{
			ft_error("error: operator unknown");
			return (NULL);
		}
		else if (str[i + 1] == '<')
			return (NULL); //DLESS
		else if (str[i + 1] == '&')
			return (NULL); //AGGREG
	}
	return (NULL);
}

t_process				*check_great(char *str, int i, t_process *new)
{
	if (!str[i + 1])
		ft_putendl_fd("21sh: parse error near '>'", 2);
	else if (str[i + 1])
	{
		if (!ft_istoken(str[i + 1]))
		{
			new->token_id = GREAT;
			return (simple_redirect(new));
		}
		else if (ft_istoken(str[i + 1]) && str[i + 2] && ft_istoken(str[i + 2]))
		{
			ft_error("error: operator unknown");
			return (NULL);
		}
		else if (ft_istoken(str[i + 1]) && ft_istoken(str[i + 1]) != 2
				&& ft_istoken(str[i + 1]) != 4)
		{
			ft_error("error: operator unknown");
			return (NULL);
		}
		else if (str[i + 1] == '>')
			return (NULL); //DGREAT
		else if (str[i + 1] == '&')
			return (NULL); // AGGREG
	}
	return (NULL);
}
