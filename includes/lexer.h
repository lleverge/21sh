/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 09:54:16 by lleverge          #+#    #+#             */
/*   Updated: 2017/04/05 15:02:30 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "shell.h"

typedef enum	e_token_id
{
	PIPE,
	LESS,
	GREAT,
	DGREAT,
	DLESS,
	QUOTE,
	DQUOTE,
	CMD,
	END_LIST,
	ERROR
}				t_token_id;

typedef struct		s_lexer
{
	int				token_id;
	char			*content;
	char			**cmd;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}					t_lexer;

typedef struct		s_parser
{
	int				stdin;
	int				stdout;
	int				shutout_out;
	int				shutout_in;
	int				token;
	char			**content;
	struct s_parser	*next;
}					t_parser;

/*
**lexer.c
*/
t_lexer				*lexer(char *cmd, t_ult *ult);

/*
**ft_strsplit_ws.c
*/
char				**ft_strsplit_ws(char const *s);

/*
**token_sep.c
*/
int					is_sep(char c);
int					is_and(char *str, int i);
int					is_pipe(char *str, int i);
int					is_quote(char *str, int i);
int					is_dquote(char *str, int i);

/*
**token_list.c
*/
int					get_token_id(char *str);
t_lexer				*lexer_list(t_lexer *list, char *str, char **cmd);

/*
**free_tools.c
*/
void				free_lexer(t_lexer **lexer);

/*
**lexer_error.c
*/
int					lexer_error(t_lexer *list);

/*
**parser_list.c
*/
void				free_parser(t_parser **parser);
t_parser			*fill_parser(t_parser *list, t_lexer *list_lex, int token);

/*
**parser.c
*/
char				**parser(t_lexer *list);

/*
**manage_io.c
*/
int					manage_io_files(t_ult *ult, t_lexer *list,
									t_parser *process, int token);
/*
**fork.c
*/
char				*search_path(char **path_tab, char **cmd);

/*
**do_pipe.c
*/
int					do_pipe(t_ult *ult, t_lexer *list);

/*
**io_redir.c
*/
void				open_redir(t_ult *ult, t_lexer *lex);
int					fd_len(char *str, int i);
#endif
