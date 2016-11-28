/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:00:01 by lleverge          #+#    #+#             */
/*   Updated: 2015/11/28 11:35:09 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*tmpdst;
	unsigned char	*tmpsrc;
	size_t			i;

	i = 0;
	tmpdst = (unsigned char *)dst;
	tmpsrc = (unsigned char *)src;
	while (i < n && tmpsrc[i] != (unsigned char)c)
	{
		tmpdst[i] = tmpsrc[i];
		i++;
	}
	if (tmpsrc[i] == (unsigned char)c)
	{
		tmpdst[i] = tmpsrc[i];
		i++;
		return (tmpdst + i);
	}
	else
		return (NULL);
}
