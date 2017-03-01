/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 09:23:51 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/01 09:24:36 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

char		*ft_strrpbrk(const char *s1, const char *s2)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = (char*)s1 + ft_strlen(s1) - 1;
	while (s2[i])
	{
		tmp = ft_strrchr(s1, (int)s2[i]);
		if (tmp != NULL)
		{
			if (tmp < ret)
				ret = tmp;
		}
		i++;
	}
	if (tmp == NULL)
		return ((char*)s1);
	return (ret + 1);
}
