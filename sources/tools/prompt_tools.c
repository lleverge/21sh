/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:23:22 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/30 13:55:10 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			is_cmd_empty(char *cmd)
{
	char	*tmp;

	tmp = cmd;
	while (*tmp)
	{
		if (!ft_isspace(*tmp))
			return (0);
		tmp++;
	}
	return (1);
}

char		*copy_cmd(char *cmd)
{
	char	*tmp;

	tmp = ft_strdup(cmd);
	return (tmp);
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
