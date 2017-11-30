/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnumword.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 17:26:24 by vfrolich          #+#    #+#             */
/*   Updated: 2017/06/22 17:57:35 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_isalnumword(char *str)
{
	while (*str)
	{
		if (!ft_isalpha(*str) && !ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
