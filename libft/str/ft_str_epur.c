/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_epur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 14:36:06 by vfrolich          #+#    #+#             */
/*   Updated: 2017/06/22 19:10:53 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_str_epur(char *str)
{
	size_t	len;
	char	*dest;

	while (*str && !ft_isalnum(*str))
		str++;
	len = ft_strlen(str);
	if (!(dest = ft_strnew(len)))
		return (NULL);
	len = 0;
	while (*str)
	{
		dest[len] = *str;
		len++;
		str++;
	}
	return (dest);
}
