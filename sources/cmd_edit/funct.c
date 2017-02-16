/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 15:08:36 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/16 15:45:47 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void		init_func1(t_func1 *func)
{
	func[UP] = &move_up;
	func[DOWN] = &move_down;
	func[LEFT] = &move_left;
	func[RIGHT] = &move_right;
	func[DEL] = &del_at;
	func[HOME] = &home;
	func[END] = &end;
	func[FWORD] = &fword;
	func[BWORD] = &bword;
	func[CP] = &select_c;
	func[SUP] = &del;
	func[PAST] = &past;
}

void		init_func2(t_fun2 *func)
{
	func[CLEFT] = &smove_left;
	func[CRIGHT] = &smove_right;
}
