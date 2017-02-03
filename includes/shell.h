/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:43:41 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/03 16:27:29 by lleverge         ###   ########.fr       */
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
# define BLUE "[34m"
# define CYAN "[36m"
# define RESET "[39m"
# define GREEN "[32m"
# define YELLOW "[33m"
# define MAGENTA "[35m"

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
}					t_term;

typedef struct		s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct		s_ult
{
	t_term			*term;
	t_env			*env;
	char			**path;
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
t_term				*init_term();

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

/*
**display_tools.c
*/
void				print_list(t_env *env);

/*
**prompt.c
*/
void				ft_putstr_sp(char *str);
void				color(char *color, char *target);
void				prompt(t_env *env);

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
