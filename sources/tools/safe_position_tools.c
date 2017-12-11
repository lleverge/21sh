/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_position_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:31:45 by vfrolich          #+#    #+#             */
/*   Updated: 2017/12/11 17:00:36 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char	*get_cdir(t_env *env)
{
	char	*cdir;
	char	*old;

	cdir = NULL;
	cdir = getcwd(cdir, 256);
	if (!cdir)
	{
		if ((old = get_data(env, "OLDPWD")))
			return (old);
		if ((old = get_data(env, "HOME")))
			return (old);
		ft_putendl_fd("21sh: neither OLDPWD nor OLDPWD are set", 2);
		exit(1);
	}
	return (cdir);
}
