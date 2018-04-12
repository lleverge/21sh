/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:54:50 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 16:10:01 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

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
