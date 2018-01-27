/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 11:36:02 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/27 14:58:33 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

t_env		*envlist_cpy(t_env *src)
{
	t_env	*new;

	if (!src)
		return (NULL);
	if (!(new = (t_env *)malloc(sizeof(t_env))))
	{
		ft_putendl_fd("21sh : allocation error, abort.", 2);
		exit(3);
	}
	new->name = ft_strdup(src->name);
	new->content = ft_strdup(src->content);
	new->next = envlist_cpy(src->next);
	return (new);
}
