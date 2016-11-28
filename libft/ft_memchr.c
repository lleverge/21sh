/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:46:09 by lleverge          #+#    #+#             */
/*   Updated: 2015/11/28 10:35:33 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmps;
	size_t			i;

	tmps = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*tmps == (unsigned char)c)
			return ((void *)tmps);
		tmps++;
		i++;
	}
	return (NULL);
}
