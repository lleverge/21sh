/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_shellvar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 19:10:42 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/29 20:11:24 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

char		*get_del_string(char *content)
{
	int		i;
	int		w_start;

	i = 0;
	while (content[i] && content[i] != '$')
		i++;
	w_start = i;
	i++;
	while (content[i] && ft_isalnum(content[i]))
		i++;
	if ((i - w_start) <= 0)
		return (NULL);
	return (ft_strsub(content, w_start, i - w_start));	
}
