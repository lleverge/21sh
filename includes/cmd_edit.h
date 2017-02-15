/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_edit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:26:39 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/15 18:39:04 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EDIT_H
# define CMD_EDIT_H
# include <shell.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>

# define BUFFER *(unsigned int *)buffer

typedef enum		e_enum
{
	LEFT_KEY = 4479771,
	RIGHT_KEY = 4414235,
	UP_KEY = 4283163,
	DOWN_KEY = 4348699,
	ESC_KEY = 27,
	SPACE_KEY = 32,
	DEL_KEY = 127,
	RET_KEY = 10,
	SUP_KEY = 2117294875,
	HOME_KEY = 4741915,
	END_KEY = 4610843,
	PAGE_UP_KEY = 2117425947,
	PAGE_DOWN_KEY = 2117491483,
	TAB_KEY = 9,
	CRTL_A_KEY = 1,
}					t_enum;

typedef struct		s_cursor
{
	int				x;
	int				y;
}					t_cursor;

typedef struct		s_input
{
	t_cursor		*curs;
	char			*cmd_line;
	char			*cp;
	int				lprom;
}					t_input;

typedef struct		s_edit
{
	t_input			*input;
	t_env			*env;
	t_term			*termi;
	int				ret;
	int				pid;
	int				fd;
	char			*absol_path;
}					t_edit;

/*
**init_input.c
*/
t_input				*init_input(void);

/*
**init_edit.c
*/
t_edit				*init_edit(t_edit *ed, char **environ);

/*
**init_cursor.c
*/
t_cursor			*init_cursor(void);

/*
**prompt.c
*/
int					prompt(t_edit *ed);

/*
**edit_tools.c
*/
void				use_ncap(char *cap, int n);
void				use_cap(char *cap);

/*
**ft_keyhook.c
*/
int					ft_keyspot(t_edit *ed);
#endif
