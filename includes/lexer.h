/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 09:54:16 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/17 22:00:16 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "shell.h"

typedef enum	e_token_id
{
	SAND = 0,
	PIPE = 1,
	LESS = 2,
	GREAT = 3,
	DGREAT = 4,
	DLESS = 5,
	QUOTE = 6,
	DQUOTE = 7,
	AND = 8,
	OR = 9,
	AGGREG = 11,
	SEPARATOR = 12,
	NEWLINE = 13,
	TOK_WORD = 14,
}				t_token_id;

typedef struct		s_lexer
{
	t_token_id		token_id;
	char			*content;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}					t_lexer;

/*
**lexer_to_str.c
*/
char				*lexer_to_str(t_lexer *lex);
t_lexer				*lexdup(t_lexer *lexlist);

char				**cmd_format(char *cmd);


/*
**format_arg.c
*/
int					is_quoted_lex(t_lexer *node, t_lexer *lexlist);
int 				count_allwords(t_lexer *lex, t_lexer *lexlist);
int					split_words(char *src, char **dest, int i);

/*
**init_lexproc.c
*/
t_lexer			*lex_from_proc(t_process *proc);

/*
**lexer.c
*/
t_process			*new_lexer(char *str, t_process *proc_list);
int					check_aggreg(char *str, int i);
char				*ft_strnosp(char *str);
t_job				*set_jobs(t_lexer *lex);
t_lexer				*fill_lexer(t_ult *ult);
int					seek_and_exec(t_ult *ult, t_process *proc,
								char **cmd_tab, int fd[2]);
int					check_linker(t_job **job_li, char *cmd, int i);

/*
**lexer2.c
*/
void				group_token(t_lexer **lexer);

/*
**check_token.c
*/
t_process			*check_pipe(char *str, int i, t_process *new);
t_process			*check_and(char *str, int i, t_process *new);
t_process			*check_less(char *str, int i, t_process *new);
t_process			*check_great(char *str, int i, t_process *new);

/*
**ft_isbadtoken.c
*/
int					ft_isbadtoken(char c);

/*
**token_recognizer.c
*/
int					is_token_char(char c);
t_token_id			which_token(char c);

/*
**new_lexer.c
*/
t_lexer				*init_lexer(char *cmd);
void				lex_push(t_lexer *new, t_lexer **lex_list);

/*
**quote_prompt.c
*/
char				*prompt_until_quote(t_ult *ult, t_token_id tok_id);
int					check_closed_quote(t_lexer **list);
t_lexer				*quote_tok(t_lexer *lexlist, t_ult *ult);

/*
**quote_hander.c
*/
void				get_final_string(t_lexer **lexlist, char **buffer);

/*
**quote_hander_2.c
*/
t_lexer				*new_word_init(char **raw_buff, t_token_id t_id);
t_lexer				*end_prompted_extract(char **raw_buff, t_token_id t_id);

/*
**pipe_prompt.c
*/
t_lexer				*prompt_pipe(t_lexer *lex, t_ult *ult);

/*
**parse_error.c
*/
int					parse_error(t_lexer *lexer, int error_fd);

/*
**merge_quotes.c
*/
int					count_merge_token(t_lexer *lex);
t_lexer				*merge_token(t_lexer *lex);

/*
**ft_strsplit_ws.c
*/
char				**ft_strsplit_ws(char const *s);

/*
**ft_strsplit_tok.c
*/
int					ft_istoken(char c);
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
t_lexer				*create_lexer_node(char *str);
void				lex_free_one(t_lexer *lexnode);
void				lex_free_all(t_lexer *lexlist);

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
