/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:53:19 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/12 15:53:22 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

char		*get_node_content(t_env *env, char *str)
{
	while (env)
	{
		if (!ft_strcmp(env->name, str))
			return (ft_strdup(env->content));
		env = env->next;
	}
	return (NULL);
}
