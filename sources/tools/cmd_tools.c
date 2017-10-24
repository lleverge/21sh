/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:54:50 by vfrolich          #+#    #+#             */
/*   Updated: 2017/10/23 17:25:48 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_extracter(char *s, char *to_del)
{
	char	*tmp;
	char	*output;

	if (!s || !ft_strstr(s, to_del) ||
		ft_strlen(to_del) >= ft_strlen(s))
		return (NULL);
	tmp = ft_strsub(s, 0, ft_strstr(s, to_del) - s);
	output = ft_strjoin(tmp, ft_strstr(s, to_del) + ft_strlen(to_del));
	ft_strdel(&tmp);
	return (output);
}
