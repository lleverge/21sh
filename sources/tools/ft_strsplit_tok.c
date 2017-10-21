/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 14:15:09 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/21 17:28:57 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				ft_istoken(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	else if (c == '|')
		return (3);
	else if (c == '&')
		return (4);
	else
		return (0);
}

static int		ft_count(char const *s)
{
	int cmp;
	int	i;

	cmp = 0;
	i = 0;
	while (*s)
	{
		if (i == 1 && ft_istoken(*s))
			i = 0;
		if (i == 0 && !ft_istoken(*s))
		{
			i = 1;
			cmp++;
		}
		s++;
	}
	return (cmp);
}

static int		ft_nstr(char const *s)
{
	int	len;

	len = 0;
	while (*s && !ft_istoken(*s))
	{
		s++;
		len++;
	}
	return (len);
}

char			**ft_strsplit_tok(char const *s)
{
	char	**t;
	int		i;
	int		word_nb;

	if (!s)
		return (NULL);
	i = 0;
	word_nb = ft_count(s);
	t = (char **)malloc(sizeof(char *) * (ft_count(s) + 1));
	if (t == NULL)
		return (NULL);
	while (word_nb--)
	{
		while (*s && ft_istoken(*s))
			s++;
		t[i] = ft_strsub((const char *)s, 0, ft_nstr(s));
		if (t[i] == NULL)
			return (NULL);
		s = s + ft_nstr(s);
		i++;
	}
	t[i] = NULL;
	return (t);
}
