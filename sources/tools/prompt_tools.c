/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:23:22 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/25 15:29:39 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void		prompt2(char *new, char *tmp, char *home)
{
	color(GREEN, "");
	ft_putstr("~");
	new = ft_strsub(tmp, ft_strlen(home), ft_strlen(tmp));
	ft_putstr_sp(new);
	color(RESET, "");
	ft_strdel(&new);
}

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
