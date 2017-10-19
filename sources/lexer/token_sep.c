/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 10:54:13 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/19 15:47:03 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

int			is_sep(char c)
{
	return (c == '>' || c == '<' || c == '&' || c == '|');
}

int			is_or(char *str, int i)
{
	return (str[i + 1] != '|') ? 0 : 1;
}

int			is_and(char *str, int i)
{
	return (str[i + 1] != '&') ? 0 : 1;
}

int			is_pipe(char *str, int i)
{
	return (str[i + 1] != '|') ? 0 : 1;
}

int			is_quote(char *str, int i)
{
	int		start;

	start = i;
	while (str[i + 1] != '\'')
		i++;
	return (i - start + 2);
}

int			is_dquote(char *str, int i)
{
	int		start;

	start = i;
	while (str[i + 1] != '\"')
		i++;
	return (i - start + 2);
}
