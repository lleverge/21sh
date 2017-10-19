/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/19 19:19:52 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int					new_lexer(char *str)
{
	int		i;

	i = 0;
	ft_putendl(str);
	while (str[i])
	{
		if (ft_istoken(str[i]))
		{
			if (ft_istoken(str[i]) == 1)
				check_less(str, i);
			if (ft_istoken(str[i]) == 2)
				check_great(str, i);
			if (ft_istoken(str[i]) == 3)
				check_pipe(str, i);
			if (ft_istoken(str[i]) == 4)
				check_and(str, i);
		}
		i++;
	}		 
	return (0);
}
