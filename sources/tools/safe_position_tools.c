/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_position_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:31:45 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/09 14:53:48 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char	*get_cdir(t_env *env)
{
	char	*cdir;
	char	*old;
	t_ult	*ult;

	cdir = NULL;
	ult = NULL;
	cdir = getcwd(cdir, 256);
	if (!cdir)
	{
		if ((old = get_node_content(env, "OLDPWD")))
			return (old);
		if ((old = get_node_content(env, "HOME")))
			return (old);
		ft_putendl_fd("21sh: neither OLDPWD nor OLDPWD are set, abort", 2);
		ult = stock_ult(ult, 1);
		reset_term(ult->term);
		exit(1);
	}
	return (cdir);
}
