/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:45:12 by vfrolich          #+#    #+#             */
/*   Updated: 2017/06/22 19:16:06 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst_t;
	unsigned char	*src_t;

	i = 0;
	dst_t = dst;
	src_t = (unsigned char *)src;
	while (i < n)
	{
		if (src_t[i] == (unsigned char)c)
		{
			dst_t[i] = src_t[i];
			return (&dst_t[i + 1]);
		}
		dst_t[i] = src_t[i];
		i++;
	}
	return (NULL);
}
