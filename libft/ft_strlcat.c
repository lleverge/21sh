/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 09:16:11 by lleverge          #+#    #+#             */
/*   Updated: 2015/11/28 13:17:02 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*tmpdst;
	const char	*tmpsrc;
	size_t		i;
	size_t		dstlen;

	tmpdst = dst;
	tmpsrc = src;
	i = size;
	while (i-- && *tmpdst)
		tmpdst++;
	dstlen = tmpdst - dst;
	i = size - dstlen;
	if (i == 0)
		return (dstlen + ft_strlen(tmpsrc));
	while (*tmpsrc)
	{
		if (i != 1)
		{
			*tmpdst++ = *tmpsrc;
			i--;
		}
		tmpsrc++;
	}
	*tmpdst = '\0';
	return (dstlen + (tmpsrc - src));
}
