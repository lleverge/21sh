/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 13:44:22 by lleverge          #+#    #+#             */
/*   Updated: 2015/12/01 17:17:02 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*memzone;
	size_t			i;

	i = 0;
	memzone = NULL;
	memzone = (unsigned char *)malloc(sizeof(void) * size);
	if (!memzone)
		return (NULL);
	while (size)
	{
		memzone[i] = 0;
		i++;
		size--;
	}
	return ((void *)memzone);
}
