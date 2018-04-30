/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 18:48:43 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/30 11:56:54 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

char		*cpy_node_content(t_env *env, char *str)
{
	while (env)
	{
		if (!ft_strcmp(env->name, str))
			return ((env->content));
		env = env->next;
	}
	return (NULL);
}
