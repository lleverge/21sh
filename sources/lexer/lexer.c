/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:45:15 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/21 17:27:47 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

int						check_aggreg(char *str, int i)
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

char					*ft_strnosp(char *str)
{
	int		count;
	int		strlen;
	int		i;
	int		j;
	char	*nosp;

	count = 0;
	strlen = ft_strlen(str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			count++;
		i++;
	}
	if (!(nosp = (char *)malloc(sizeof(char) * (strlen - count))))
	{
		ft_putendl_fd("21sh: ft_strnosp malloc failed", 2);
		exit(-1);
	}
	while (*str)
	{
		if (!ft_isspace(*str))
		{
			nosp[j] = *str;
			j++;
		}
		str++;
	}
	return (nosp);
}

int						new_lexer(char *str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (ft_istoken(str[i]))
		{
			if (ft_istoken(str[i]) == 1)
				ret = check_less(str, i);
			else if (ft_istoken(str[i]) == 2)
				ret = check_great(str, i);
			else if (ft_istoken(str[i]) == 3)
				ret = check_pipe(str, i);
			else if (ft_istoken(str[i]) == 4)
				ret = check_and(str, i);
		}
		if (ret == -1)
			return (-1);
		i++;
	}
	return (0);
}
