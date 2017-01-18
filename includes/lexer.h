/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 09:54:16 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/18 09:54:17 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"
# include "shell.h"

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

typedef struct		s_node
{
	int				token_id;
	char			*content;
	char			**cmd;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

#endif
