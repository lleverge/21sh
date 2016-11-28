/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:26:17 by lleverge          #+#    #+#             */
/*   Updated: 2015/12/07 13:45:21 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	robert;

	i = 0;
	robert = c;
	tmp = (unsigned char *)b;
	while (i < len)
	{
		tmp[i] = robert;
		i++;
	}
	return (b);
}
