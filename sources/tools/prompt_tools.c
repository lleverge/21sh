/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:23:22 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/03 17:35:04 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char		*get_data(t_env *env, char *ref_name)
{
	while (env)
	{
		if (ft_strcmp(env->name, ref_name) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}
