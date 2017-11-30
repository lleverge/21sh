/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strgen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 12:30:47 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/09 12:35:43 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*strgen(size_t lenght)
{
	char	*line;

	if (!(line = ft_strnew(lenght)))
	{
		ft_putstr_fd("no memory	available for string buffer, need: ", 2);
		ft_putnbr(lenght);
		ft_putendl_fd(" abort.", 2);
		exit(1);
	}
	return (line);
}
