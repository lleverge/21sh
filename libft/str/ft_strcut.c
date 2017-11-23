/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:12:37 by vfrolich          #+#    #+#             */
/*   Updated: 2017/06/22 19:10:28 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcut(char *str, char c)
{
	size_t	diff;
	char	*tmp;

	tmp = str;
	diff = 0;
	while (*tmp)
	{
		if (*tmp == c)
			diff++;
		tmp++;
	}
	diff = ft_strlen(str) - diff;
	tmp = ft_strnew(diff);
	while (*str)
	{
		if (*str != c)
		{
			*tmp = *str;
			tmp++;
		}
		str++;
	}
	return (tmp);
}
