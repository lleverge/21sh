/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:33:02 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/27 15:26:38 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "shell.h"
# include "lexer.h"

/*
**env_builtin.c
*/
t_ult					*setting_tmp_ult(t_ult *ult, t_env *env);
t_lexer					*fill_lexer_env(t_ult *ult, char *cmd);
char					*word_array_to_str(char **args_arr);
int						env_builtin(t_ult *ult, char **arg);
void					job_launch_env(t_job *job_li, t_ult *ult);

/*
**env_builtin_tools.c
*/
t_env					*envlist_cpy(t_env *src);
int						index_start_newtab(char **cmd);
int						check_opt(char *opt);
char					**tab_dup(char **src, int index_start_newtab);

/*
**setenv.c
*/
t_env					*add_all_env(t_ult *ult, char **cmd);
t_env					*split_to_set(t_ult *ult, char **arg);
t_env					*set_env(t_env **env, char *name,
								char *value);

/*
**setunsetenv.c
*/
void					unset_error(char *cmd);
t_env					*split_to_unset(t_ult *ult, char **arg);

/*
**cd.c
*/
int						ft_cd(t_env **env, char **arg);

/*
**cd_2.c
*/
int						check_for_access(char *path);

/*
**echo.c
*/
int						ft_echo(char **str);

/*
**exit.c
*/
int						clean_exit(char **arg, int ret);

#endif
