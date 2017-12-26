/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:33:02 by vfrolich          #+#    #+#             */
/*   Updated: 2017/12/26 14:21:56 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <shell.h>

/*
**unsetenv.c
*/
t_env					*split_to_unset(t_ult *ult);
int						unset_env(char *name, t_env *envlist);

/*
**setenv.c
*/
t_env					*split_to_set(t_ult *ult);
t_env					*set_env(t_env *env, char *name, char *value);

/*
**cd.c
*/
int						ft_cd(t_env *env, char **arg);

/*
**echo.c
*/
int						ft_echo(char **str);

/*
**exit.c
*/
int						clean_exit(char **arg, int ret);

#endif
