/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:49:22 by vfrolich          #+#    #+#             */
/*   Updated: 2017/06/22 19:16:02 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	char			*tmp;
	char			d;

	d = c;
	i = 0;
	tmp = (char *)s;
	while (i < n)
	{
		if (tmp[i] == d)
			return (&tmp[i]);
		i++;
	}
	return (NULL);
}
