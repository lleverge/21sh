/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/20 12:20:57 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

int				check_aggreg(char *str, int i)
{
	int		j;
	int		fdi1;
	int		fdi2;
	char	*fd2;
	char	*fd1;

	j = i - 1;
	while (ft_isdigit(str[j]))
		j--;
	fd1 = ft_strsub(str, j + 1, i - j - 1);
	fdi1 = ft_atoi(fd1);
	j = i + 2;
	while (ft_isdigit(str[j]))
		j++;
	fd2 = ft_strsub(str, i + 2, j - i);
	fdi2 = ft_atoi(fd2);
	return (0);
}

int					new_lexer(char *str)
{
	int		i;

	i = 0;
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
