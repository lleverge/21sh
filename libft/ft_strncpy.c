/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 09:11:29 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/23 16:45:31 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	count;

	count = 0;
	while (dst && src[count] != '\0' && count < n)
	{
		dst[count] = src[count];
		count++;
	}
	while (src && dst && count < n)
	{
		dst[count] = '\0';
		count++;
	}
	return (dst);
}
