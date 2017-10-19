/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 09:54:16 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/19 12:48:31 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "shell.h"

typedef enum	e_token_id
{
	PIPE = 1,
	LESS = 2,
	GREAT = 3,
	DGREAT = 4,
	DLESS = 5,
	QUOTE = 6,
	DQUOTE = 7,
	AND = 8,
	OR = 9,
	SEPARATOR = 10,
}				t_token_id;

typedef struct		s_lexer
{
	int				token_id;
	char			*content;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}					t_lexer;

/*
**lexer.c
*/
t_lexer				*lexer(char *cmd, t_ult *ult);

/*
**ft_strsplit_ws.c
*/
char				**ft_strsplit_ws(char const *s);

/*
**ft_strsplit_tok.c
*/
char				**ft_strsplit_tok(char const *s);

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
t_lexer				*lexer_list(t_lexer *list, char *str);

/*
**free_tools.c
*/
void				free_lexer(t_lexer **lexer);

/*
**lexer_error.c
*/
int					lexer_error(t_lexer *list);

/*
**parser.c
*/
int					parser(t_lexer *list, t_ult *ult);

/*
**manage_io.c
*/

/*
**fork.c
*/
char				*search_path(char **path_tab, char **cmd);

/*
**do_pipe.c
*/
int					fork_pipe(t_ult *ult, char **cmd1);

/*
**io_redir.c
*/
void				open_redir(t_ult *ult, t_lexer *lex);
int					fd_len(char *str, int i);
#endif
