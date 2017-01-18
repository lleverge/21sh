/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 09:54:16 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/18 12:32:31 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <shell.h>

typedef enum	e_token_id
{
	PIPE,
	LESS,
	GREAT,
	DGREAT,
	DLESS,
	OR,
	AND,
	QUOTE,
	DQUOTE,
	CMD,
	BQUOTE,
	DOLLAR,
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

int					is_sep(char c);
int					is_and(char *str, int i);
int					is_pipe(char *str, int i);
int					is_quote(char *str, int i);
int					is_dquote(char *str, int i);
int					get_token_id(char *str);
t_lexer				*lexer_list(t_lexer *list, char *str);

#endif
