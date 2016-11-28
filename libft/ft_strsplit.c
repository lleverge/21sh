/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:11:58 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/21 15:15:43 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_countwords(char const *s, char c)
{
	int	cmp;
	int	i;

	cmp = 0;
	i = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			cmp++;
		}
		s++;
	}
	return (cmp);
}

static int		ft_countchar(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**t;
	int		i;
	int		word_nb;

	i = 0;
	word_nb = ft_countwords(s, c);
	t = (char **)malloc(sizeof(char *) * (ft_countwords(s, c)) + 1);
	if (t == NULL || s == NULL)
		return (NULL);
	while (word_nb--)
	{
		while (*s && *s == c)
			s++;
		t[i] = ft_strsub((const char *)s, 0, ft_countchar(s, c));
		if (t[i] == NULL)
			return (NULL);
		s = s + ft_countchar(s, c);
		i++;
	}
	t[i] = NULL;
	return (t);
}
