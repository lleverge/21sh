/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:09:23 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/24 17:10:20 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <stdio.h>
# include <fcntl.h>

# define RED "[31m"
# define PURPLE "[1;35m"
# define GREEN "[32m"
# define CYAN "[0;36m"
# define BLUE "[1;34m"
# define RESET "[39m"

typedef struct stat		t_stat;
typedef struct winsize	t_winsize;
typedef struct termios	t_termios;

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_term
{
	int				fd;
	t_termios		termios;
	t_winsize		ws;
}					t_term;

typedef struct		s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct		s_exec
{
	pid_t			pid;
	int				fd[2];
	int				fd_write;
	int				fd_read;
	int				stdin_cp;
	int				stdout_cp;
}					t_exec;

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_ult
{
	t_exec			*exec;
	t_term			*term;
	t_env			*env;
	t_pos			*pos;
	char			**path;
	t_hist			*hist;
	char			*cmd;
	int				ret;
}					t_ult;

/*
**init_ult.c
*/
t_ult				*init_ult(t_ult *ult, char **environ);

/*
**init_env.c
*/
t_env				*env_cpy(t_env *envtmp, t_env *env);
t_env				*var_cpy(t_env *start, t_env *cpy);
t_env				*env_in_list(char *envar, t_env *start);
t_env				*fill_env(char **environ);

/*
**init_term.c
*/
void				init_term2(t_term *termi);
t_term				*init_term(void);

/*
**init_hist.c
*/
t_hist				*init_hist(t_hist *hist);

/*
**hist.c
*/
void				fill_hist(t_hist **hist, char *cmd);
void				hist_full(t_hist **hist);
void				add_hist(t_hist **start, char *cmd);

/*
**env_tools.c
*/
int					count_tablen(char **tab);
char				**ft_tabdup(char **tab);
char				*getvarcontent(char *envar);
char				*getvarname(char *envar);
t_env				*env_cpy(t_env *envtmp, t_env *env);

/*
**prompt_tools.c
*/
void				prompt2(char *new, char *tmp, char *home);
char				*get_data(t_env *env, char *ref_name);
char				*copy_cmd(char *cmd);

/*
**display_tools.c
*/
void				print_list(t_env *env);

/*
**ft_size.c
*/
void				get_ws(t_term *termi);

/*
**free_tools.c
*/
void				free_env(t_env **head);
void				free_tab(char **tab);

/*
**init_tools.c
*/
char				*get_node_content(t_env *env, char *str);
#endif
