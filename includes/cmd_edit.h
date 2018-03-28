/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_edit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:26:39 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/28 19:51:13 by vfrolich         ###   ########.fr       */
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

# define T_UP ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65))
# define T_DOWN ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66))
# define T_LEFT ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68))
# define T_RIGHT ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67))
# define T_DEL ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51))
# define T_HOME ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 72))
# define T_END ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 70))
# define T_CUT (buffer[0] == 11 && buffer[1] == 00)
# define T_PAS (buffer[0] == 16 && buffer[1] == 00)
# define T_CPY (buffer[0] == 9 && buffer[1] == 00)
# define PREV_WORD1 ((buffer[0] == 27 && buffer[1] == 27))
# define PREV_WORD2 ((buffer[2] == 91 && buffer[3] == 68))
# define NEXT_WORD2 ((buffer[2] == 91 && buffer[3] == 67))
# define NEXT_WORD1 ((buffer[0] == 27 && buffer[1] == 27))
# define PREV_WORD ((PREV_WORD1 && PREV_WORD2))
# define NEXT_WORD ((NEXT_WORD1 && NEXT_WORD2))
# define CHAR ((*buffer >= '!' && *buffer <= '~'))
# define WHITE_SP ((*buffer == ' '))
# define BACK_SPACE ((*buffer == 127))
# define UP_CMD_1 ((buffer[0] == 27 && buffer[1] == 27))
# define UP_CMD_2 ((buffer[2] == 91 && buffer[3] == 65))
# define UP_CMD ((UP_CMD_1 && UP_CMD_2))
# define DOWN_CMD_1 ((buffer[0] == 27 && buffer[1] == 27))
# define DOWN_CMD_2 ((buffer[2] == 91 && buffer[3] == 66))
# define DOWN_CMD ((DOWN_CMD_1 && DOWN_CMD_2))
# define T_TAB (buffer[0] == 9)

typedef struct		s_prompt
{
	char			cmd[2000];
	int				i;
	int				y;
	int				copy_mode;
	int				cursor_start;
	int				cursor_end;
	char			*copy_str;
	size_t			win_size;
	int				heredoc;
}					t_prompt;

typedef struct		s_compl
{
	int 			cursored;
	char			*name;
	struct 	s_compl *next;
	struct 	s_compl	*prev;
}					t_compl;

/*
**init_prompt.c
*/
t_prompt			*init_prompt(void);
t_prompt			*stock_prompt(t_prompt *prompt, int i);

/*
**init_complete.c
*/
t_compl 				*get_all_cmd(char *paths, char *cmd);

/*
**init_complete2.c
*/
t_compl					*init_cmd_compl(t_ult *ult, char *cmd);

/*
**init_term.c
*/
int					reset_term(t_term *termi);
void				exit_eof(t_term *termi, t_prompt *prompt);

/*
**word_detect.c
*/
char				*word_detect(t_prompt *prompt);
int					first_word(t_prompt	*prompt);
int					empty_space(t_prompt *prompt);

/*
**select_return.c
*/
void				select_in_prompt(char *select, t_prompt *prompt);

/*
**small_prompt.c
*/
int					ask_prompt(t_compl *list);

/*
**exec_more.c
*/
void 				exec_more(t_compl *list, t_ult *ult);


/*
**print_compl.c
*/
size_t				word_per_line(t_compl *list);
void				print_options(t_compl *list);

/*
**print_compl.c
*/
void				free_all_choices(t_compl *elem);

/*
**print_tools.c
*/
size_t				get_term_size(char *field);
size_t				get_largest_word(t_compl *list);
size_t				word_per_line(t_compl *list);
void				clr_screen(t_compl *list);
size_t 				count_lines(t_compl *list);
size_t				count_entries(t_compl *list);

/*
**select_actions.c
*/
void				select_next(t_compl *list);
void				select_prev(t_compl *list);
void				do_selection(t_compl *list, t_prompt *prompt);


/*
**prompt.c
*/
void				get_prompt(t_env *env);
void				color(char *color, char *str);

/*
**tcaps.c
*/
void				termcap(t_ult *ult);
void				prompt_print(t_prompt *prompt, int show_cursor);
void				prompt_shell(t_prompt *prompt, char *buff, t_ult *ult);
void				reset_prompt(t_prompt *prompt);
void				reset_prompt_heredoc(t_prompt *prompt, int show_cursor);
void				print_cursor(t_prompt *prompt, int show_cursor, int i);

/*
**insert.c
*/
void				delete(t_prompt *prompt, char *buffer);
void				backspace(t_prompt *prompt, char *buffer);
void				space(t_prompt *prompt, char *buffer);
void				charac(t_prompt *prompt, char *buffer);

/*
**move.c
*/
void				down(t_prompt *prompt, char *buffer, t_ult *ult);
void				up(t_prompt *prompt, char *buffer, t_ult *ult);
void				left(t_prompt *prompt, char *buffer);
void				right(t_prompt *prompt, char *buffer);

/*
**cut.c
*/
void				cut(t_prompt *prompt, char *buffer, int i);
void				paste(t_prompt *prompt, char *buffer);
void				copy(t_prompt *prompt, char *buffer, int i);

/*
**edit_tools.c
*/
int					get_intel(t_env *env, char *str);
int					ft_putchar_int(int c);
void				reset_prompt2(t_prompt *prompt, t_ult *ult);
void				print_backsp(t_prompt *prompt, int show_cursor);
void				reset(t_prompt *prompt);

/*
**homend.c
*/
void				next_word(t_prompt *prompt, char *buffer);
void				previous_word(t_prompt *prompt, char *buffer);
void				home(t_prompt *prompt, char *buffer);
void				end(t_prompt *prompt, char *buffer);

/*
**updown.c
*/
void				down_line(t_prompt *prompt, char *buffer);
void				up_line(t_prompt *prompt, char *buffer);

/*
**main_auto.c
*/

void				main_auto(t_prompt *prompt, char *buffer, t_ult *ult);

/*
**main_auto.c
*/
void				read_compl(t_compl *list, t_prompt *prompt);

/*
**free_tools.c
*/
void				free_prompt(t_prompt **prompt);
char				*read_heredoc(t_prompt *prompt, t_ult *ult, int *sig_flag);




#endif
