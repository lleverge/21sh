/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:43:41 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/18 11:24:01 by lleverge         ###   ########.fr       */
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

#endif
