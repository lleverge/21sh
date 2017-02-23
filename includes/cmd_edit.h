/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_edit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:26:39 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/16 18:24:35 by lleverge         ###   ########.fr       */
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

# define FUNC1 14
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3
# define DEL 4
# define HOME 5
# define END 6
# define FWORD 7
# define BWORD 8
# define CP 9
# define SUP 10
# define PAST 11
# define HISTORY_UP 12
# define HISTORY_DOWN 13

# define T_UP 0x415B1B1B
# define T_DOWN 0x425B1B1B
# define T_LEFT 0x444F1B
# define T_RIGHT 0x434F1B
# define T_DEL 0x7F
# define T_HOME 0x01
# define T_END 0x05
# define T_FWORD 0x92C6
# define T_BWORD 0xAB88E2
# define T_VISUAL 0x9FC3
# define T_CUT 0x8889E2
# define T_CP 0xA7C3
# define T_SUP 0x4
# define T_PAST 0x9A88E2
# define T_ENTER 0xA
# define T_HUP 0x414F1B
# define T_HDOWN 0x424F1B
# define T_QUIT 0x4
# define T_CLEAR 0x2
# define FUNC2 2
# define CLEFT 0
# define CRIGHT 1

/*# define BUFFER *(unsigned int *)buffer

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
	}					t_enum;*/

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

typedef struct		s_key
{
	void			(*func1[FUNC1])(struct s_edit *ed);
	void			(*func2[FUNC2])(struct s_edit *ed);
	void			*buffer;
	int				*move;
	int				*cmove;
}					t_key;

typedef void		(*t_func1)(t_edit *ed);
typedef void		(*t_func2)(t_edit *ed);

/*
**init_input.c
*/
t_input				*init_input(void);

/*
**init_edit.c
*/
t_edit				*init_edit(t_edit *ed, char **environ);
int					*init_move(void);
int					*init_cmove(void);
void				init_tkey(t_edit *ed, t_key **key);

/*
**init_cursor.c
*/
t_cursor			*init_cursor(void);

/*
**funct.c
*/
void				init_func1(t_func1 *func);
void				init_func2(void/*t_func2 *func*/);

/*
**line_edition.c
*/
void				line_edition(t_key *key, t_edit *ed);

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
void				move_right(t_edit *ed);
void				move_left(t_edit *ed);
//int					ft_keyspot(t_edit *ed);
#endif
