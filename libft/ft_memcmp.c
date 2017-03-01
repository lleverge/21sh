/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:11:43 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/01 10:10:27 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			count;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	count = 0;
	if (n == 0)
		return (0);
	while (count < n)
	{
		if (str1[count] != str2[count])
			return ((int)(str1[count] - str2[count]));
		count++;
	}
	return (0);
}
