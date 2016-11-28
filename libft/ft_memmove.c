/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:29:52 by lleverge          #+#    #+#             */
/*   Updated: 2015/11/26 10:33:31 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmpdst;
	unsigned char	*tmpsrc;
	size_t			i;

	tmpdst = (unsigned char *)dst;
	tmpsrc = (unsigned char *)src;
	i = 0;
	if (dst > src)
	{
		while (len--)
			tmpdst[len] = tmpsrc[len];
	}
	else
	{
		while (len--)
		{
			*tmpdst = *tmpsrc;
			tmpdst++;
			tmpsrc++;
		}
	}
	return (dst);
}
