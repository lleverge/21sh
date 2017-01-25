/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_edit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:26:39 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/25 17:01:23 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EDIT_H
# define CMD_EDIT_H
# include <shell.h>
# include <term.h>
# include <curses.h>

typedef struct		s_cursor
{
	int				x;
	int				y;
}					t_cursor;

/*
** prompt.c**
*/
void				ft_putstr_sp(char *str);
void				color(char *color, char *target);

#endif
