/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 11:33:50 by vfrolich          #+#    #+#             */
/*   Updated: 2017/06/22 19:15:13 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_sqrt(int nb)
{
	int i;

	i = 0;
	if (nb < 0 || nb > 2147483647)
		return (0);
	while (i * i < nb)
		i++;
	if (i * i == nb)
		return (i);
	else
		return (0);
}
