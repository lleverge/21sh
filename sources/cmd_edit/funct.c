/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 15:08:36 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/16 18:21:20 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void		init_func1(t_func1 *func)
{
//	func[UP] = &move_up(ed);
//	func[DOWN] = &move_down(ed);
	func[LEFT] = &move_left;
	func[RIGHT] = &move_right;
//	func[DEL] = &del_at(ed);
//	func[HOME] = &home(ed);
//	func[END] = &end(ed);
//	func[FWORD] = &fword(ed);
//	func[BWORD] = &bword(ed);
//	func[CP] = &select_c(ed);
//	func[SUP] = &del(ed);
//	func[PAST] = &past(ed);
}

void		init_func2(/*t_func2 *fun2)*/void)
{
//	func[CLEFT] = &smove_left(ed);
//	func[CRIGHT] = &smove_right(ed);
}
