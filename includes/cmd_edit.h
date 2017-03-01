/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_edit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:26:39 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/01 12:03:44 by lleverge         ###   ########.fr       */
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

# define FUNC1 9
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3
# define DEL 4
# define HOME 5
# define END 6
# define FWORD 7
# define BWORD 8

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
char				*ft_strsupress_at(char *str, size_t pos);
int					check_max(t_edit *ed, t_cursor *curs, char *cmd_line, int index);
void				supress_end(t_edit *ed);

/*
**edit_tools2.c
*/
char				*ft_strrpbrk(const char *s1, const char *s2);

/*
**ft_keyhook.c
*/
void				move_right(t_edit *ed);
void				move_left(t_edit *ed);
void				move_up(t_edit *ed);
void				move_down(t_edit *ed);
//int					ft_keyspot(t_edit *ed);

/*
**insert_char.c
*/
char				*ft_strinsert_at(char *str, char c, size_t pos);
void				putchar_move_cursor(t_edit *ed);
void				insert_rec(t_edit *ed, int y, char *nuffer, int rec);
char				*insert_at(t_edit *ed, char *buffer, char c);

/*
**del.c
*/
void				del_at(t_edit *ed);
void				del(t_edit *ed);

/*
**homend.c
*/
void				home(t_edit *ed);
void				end(t_edit *ed);

/*
**bfword.c
*/
void				fword(t_edit *ed);
void				bword(t_edit *ed);
char				*ft_strpbrk(const char *s1, const char *s2);


/*
**ft_size.c
*/
int					cursor_to_sbuffer(t_edit *ed, int x, int y);
void				buffer_to_cursor(t_edit *ed, int pos, t_cursor *cursor);
int					line_full(t_edit *ed, int len, int y, int prompt_size);
#endif
