/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordtab_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 12:32:10 by vfrolich          #+#    #+#             */
/*   Updated: 2017/06/22 19:13:42 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		count_words(char **wordtab)
{
	int		count;
	char	**tmp;

	tmp = wordtab;
	count = 0;
	while (*tmp)
	{
		count++;
		tmp++;
	}
	return (count);
}

int		count_chars(char **wordtab)
{
	int		count;
	char	**tmp;
	char	*tmp2;

	count = 0;
	tmp = wordtab;
	while (*tmp)
	{
		tmp2 = *tmp;
		while (*tmp2)
		{
			count++;
			tmp2++;
		}
		tmp++;
	}
	return (count);
}

char	*ft_wordtab_to_str(char **wordtab)
{
	char	*dest;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	dest = ft_strnew(count_chars(wordtab) + count_words(wordtab));
	while (wordtab[k])
	{
		j = 0;
		while (wordtab[k][j])
		{
			dest[i] = wordtab[k][j];
			j++;
			i++;
		}
		dest[i] = 32;
		i++;
		k++;
	}
	dest[i] = '\0';
	return (dest);
}
