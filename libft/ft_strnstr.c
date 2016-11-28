/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:45:25 by lleverge          #+#    #+#             */
/*   Updated: 2015/11/28 11:08:19 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*found;
	char	*reset;
	size_t	i;
	size_t	j;

	i = 0;
	reset = (char *)s2;
	while (*s1 && i < n)
	{
		found = (char *)s1;
		j = i;
		while (*s1 && *s2 && *s1 == *s2 && j < n)
		{
			s1++;
			s2++;
			j++;
		}
		if (!*s2)
			return (found);
		s1 = found;
		s2 = reset;
		s1++;
		i++;
	}
	return (NULL);
}
