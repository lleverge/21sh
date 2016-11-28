/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:11:43 by lleverge          #+#    #+#             */
/*   Updated: 2015/12/07 13:48:03 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	if (!*tmps1 && !tmps2)
		return (0);
	while (*tmps1 == *tmps2 && n > 0)
	{
		tmps1++;
		tmps2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*tmps1 - *tmps2);
}
