/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 11:37:57 by lleverge          #+#    #+#             */
/*   Updated: 2015/12/07 15:28:43 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	char *found;
	char *reset;

	found = (char *)s1;
	reset = (char *)s2;
	if (*s2 == '\0')
		return (found);
	while (*s1)
	{
		found = (char *)s1;
		while (*s1 && *s2 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		if (!*s2)
			return (found);
		else
		{
			s1 = found;
			s2 = reset;
		}
		s1++;
	}
	return (NULL);
}
