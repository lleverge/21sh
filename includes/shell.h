/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:43:41 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/18 13:36:28 by lleverge         ###   ########.fr       */
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
# include <term.h>

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
}					t_ult;

// init_ult.c
t_ult				*init_ult(t_ult *ult, char **environ);

// init_env.c
t_env				*env_cpy(t_env *envtmp, t_env *env);
t_env				*var_cpy(t_env *start, t_env *cpy);
t_env				*env_in_list(char *envar, t_env *start);

// env_tools.c
int					count_tablen(char **tab);
char				**ft_tabdup(char **tab);
char				*getvarcontent(char *envar);
char				*getvarname(char *envar);
t_env				*env_cpy(t_env *envtmp, t_env *env);

#endif
