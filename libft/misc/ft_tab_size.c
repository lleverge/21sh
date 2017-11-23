/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 15:27:24 by vfrolich          #+#    #+#             */
/*   Updated: 2017/06/22 19:14:59 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t		ft_tab_size(char **tab)
{
	char	**tmp;
	size_t	size;

	tmp = tab;
	size = 0;
	while (*tmp)
	{
		size++;
		tmp++;
	}
	return (size);
}
