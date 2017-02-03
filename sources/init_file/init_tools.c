/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:53:19 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/03 15:55:02 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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
