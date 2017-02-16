/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:57:33 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/16 17:10:41 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

int					*init_move(void)
{
	int		*ret;

	if (!(ret = (int *)malloc(sizeof(int) * FUNC1)))
	{
		ft_putendl_fd("error: move tab malloc failed", 2);
		exit(-1);
	}
	ret[0] = T_UP;
	ret[1] = T_DOWN;
	ret[2] = T_LEFT;
	ret[3] = T_RIGHT;
	ret[4] = T_DEL;
	ret[5] = T_HOME;
	ret[6] = T_END;
	ret[7] = T_FWORD;
	ret[8] = T_BWORD;
	ret[9] = T_VISUAL;
	ret[10] = T_SUP;
	ret[11] = T_PAST;
	ret[12] = T_HUP;
	ret[13] = T_HDOWN;
	return (ret);
}

int					*init_cmove(void)
{
	int		*ret;

	if (!(ret = (int *)malloc(sizeof(int) * FUNC2)))
	{
		ft_putendl_fd("error: cmove tab malloc failed", 2);
		exit(-1);
	}
	ret[0] = T_LEFT;
	ret[1] = T_RIGHT;
	return (ret);
}

void				init_tkey(t_edit *ed, t_key **key)
{
	get_ws(ed->termi);
	if (!(*key = (t_key *)malloc(sizeof(t_key))))
	{
		ft_putendl_fd("error: key struct malloc failed", 2);
		exit(-1);
	}
	init_func1((*key)->func1);
	//init_func2((*key)->func2);
	if (!((*key)->buffer = ft_memalloc(8)))
	{
		ft_putendl_fd("error: key->buffer malloc failed", 2);
		exit(-1);
	}
	(*key)->move = init_move();
//	(*event)->cmove = init_cmove();
}

t_edit				*init_edit(t_edit *ed, char **environ)
{
	if (!(ed = (t_edit *)malloc(sizeof(t_edit))))
	{
		ft_putendl_fd("error: edit struct malloc failed", 2);
		exit(-1);
	}
	ed->env = fill_env(environ);
	ed->input = init_input();
	ed->termi = init_term();
	get_ws(ed->termi);
	return (ed);
}
