/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:33:02 by vfrolich          #+#    #+#             */
/*   Updated: 2018/02/07 20:28:14 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <shell.h>
# include <lexer.h>

/*
**env_builtin.c
*/
t_ult					*setting_tmp_ult(t_ult *ult, t_env *env);
t_lexer					*fill_lexer_env(t_ult *ult, char *cmd);
char					*word_array_to_str(char **args_arr);
int 					env_builtin(t_ult *ult, char **arg);

/*
**env_builtin_tools.c
*/
t_env					*envlist_cpy(t_env *src);
int						index_start_newtab(char **cmd);
int						check_opt(char *opt);
char					**tab_dup(char **src, int index_start_newtab);

/*
**unsetenv.c
*/
t_env					*split_to_unset(t_ult *ult);
int						unset_env(char *name, t_env *envlist);

/*
**setenv.c
*/
t_env					*split_to_set(t_ult *ult);
t_env					*set_env(t_env **env, char *name, char *value);

/*
**cd.c
*/
int						ft_cd(t_env **env, char **arg);

/*
**echo.c
*/
int						ft_echo(char **str);

/*
**exit.c
*/
int						clean_exit(char **arg, int ret);

#endif
