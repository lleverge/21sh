/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:09:23 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/15 15:12:43 by lleverge         ###   ########.fr       */
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

typedef struct			s_term
{
	int					fd;
	t_termios			termios;
	t_winsize			ws;
}						t_term;

typedef struct			s_env
{
	char				*name;
	char				*content;
	struct s_env		*next;
}						t_env;

typedef struct			s_process
{
	int					token_id;
	char				*cmd;
	int					fd[3];
	pid_t				pid;
	int					done;
	t_list				*fd_to_close;
	struct s_process	*next;
}						t_process;

typedef struct			s_job
{
	char				*cmd;
	int					linker;
	pid_t				pgid;
	t_process			*proc;
	struct s_job		*next;
}						t_job;

typedef struct			s_hist
{
	char				*cmd;
	struct s_hist		*prev;
	struct s_hist		*next;
}						t_hist;

typedef struct			s_hashelem
{
	char				*bin_name;
	char				*full_bin_name;
	struct s_hashelem	*next;
}						t_hashelem;

typedef struct			s_ult
{
	t_term				*term;
	t_env				*env;
	char				**path;
	t_hashelem			**hash_table;
	t_hist				*hist;
	int					fd[3];
	int					ret;
	char				*cmd;
}						t_ult;

/*
**init_ult.c
*/
t_ult					*init_ult(t_ult *ult, char **environ);
t_ult					*stock_ult(t_ult *ult, int i);

/*
**init_env.c
*/
t_env					*env_cpy(t_env *envtmp, t_env *env);
t_env					*var_cpy(t_env *start, t_env *cpy);
t_env					*env_in_list(char *envar, t_env *start);
t_env					*fill_env(char **environ);

/*
**init_term.c
*/
void					init_term2(t_term *termi);
t_term					*init_term(void);

/*
**init_job.c
*/
t_job					*job_list(t_job *job, char *cmd);
void					job_pushb(t_job **head, t_job *new);
t_job					*create_job_node(char *cmd);

/*
**init_process.c
*/
t_process				*process_list(t_process *proc, char *cmd);
void					proc_pushb(t_process **head, t_process *new);
t_process				*create_proc_node(char *cmd);
t_process				*stock_proc(t_process *proc, int i);

/*
**init_hist.c
*/
t_hist					*init_hist(t_hist *hist);

/*
**hist.c
*/
void					fill_hist(t_hist **hist, char *cmd);
void					hist_full(t_hist **hist);
void					add_hist(t_hist **start, char *cmd);

/*
**env_tools.c
*/
int						count_tablen(char **tab);
char					**ft_tabdup(char **tab);
char					*getvarcontent(char *envar);
char					*getvarname(char *envar);
t_env					*env_cpy(t_env *envtmp, t_env *env);

/*
**prompt_tools.c
*/
void					prompt2(char *new, char *tmp, char *home);
char					*get_data(t_env *env, char *ref_name);
char					*copy_cmd(char *cmd);

/*
**display_tools.c
*/
void					print_list(t_env *env);

/*
**ft_size.c
*/
void					get_ws(t_term *termi);

/*
**free_tools.c
*/
void					free_env(t_env **head);
void					free_tab(char **tab);
void					free_process_one(t_process *proc);

/*
**init_tools.c
*/
char					*get_node_content(t_env *env, char *str);

/*
**redirections
*/

t_process				*simple_redirect(t_process *proc);
t_process				*append_redirect(t_process *proc);
t_process				*redirect_input(t_process *proc);
t_process				*standard_fd(t_process *proc);
t_process				*heredoc(t_process *proc, t_ult *ult);
t_process				*clean_exit_heredoc(int fd[2], char **delim);
t_process				*agreg_output(t_process *proc);
t_process				*cmd_epur_agreg(t_process *proc);
char					*termcaps_heredoc(t_ult *ult);
void					heredoc_write(int fd, char *delim, t_ult *ult);
t_process				*cmd_epur_heredoc(t_process *proc);
int						check_error_redir(char *sub_cmd, char *error_char);
void					get_open_err(char *file_name, int access_mode);
char					*get_word(char *sub_cmd);
int						which_fd(char *cmd);
char					*ft_extracter(char *s, char *to_del);
int						get_start_pos(char *cmd);
int						get_epur_size(char *cmd);

/*
**hash_table
*/
t_hashelem				*hash_init(t_env *envlist);
t_hashelem				*init_hash_one(char *binary, char *full_binary);
void					destroy_path_list(t_hashelem *path_list);
t_hashelem				*get_all_binwords(char *path_string);
void					hash_push(t_hashelem *newelem, t_hashelem **elemlist);
char					*hash_search(char *cmd, t_hashelem **table);
int						hash_it(char *cmd);
t_hashelem				**table_init(t_env *envlist);
void					hash_destroy_one(t_hashelem *elem);
void					hash_destroy(t_hashelem **table);

/*
**fork.c
*/
char					**path_in_tab(t_env *env, char **cmd);
int						exe_fork2(char **cmd, char **path_tab);
int						exe_fork(t_env *env, t_process *proc, t_hashelem **table);

/*
**fork2.c
*/
void					fork_error(char **cmd, char **path_tab);
char					*search_path2(char *tmp2, char *tmp, char **path_tab,
							int i);

/*
**tools2.c
*/
int						list_size(t_env *env);

/*
**tools3.c
*/
char					*ft_getbin_path(char *cmd);
char					*ft_getbin_name(char *cmd);
char					**ft_tabdup_path(char **tab, char *content);
char					**part_tabcpy(char **tab);
char					**list_in_tab(t_env *env);

/*
**error.c
*/
void					ft_env_error(char *file);
int						env_manage_error(char *cmd);

/*
**signal.c
*/
void					main_signal_handler(void);

/*
**heredoc_signal.c
*/
void					sig_handler_heredoc(int sig);
int						*singleton_signal();

/*
**pipe.c
*/

/*
**safe_position_tools.c
*/
char					*get_cdir(t_env *env);

/*
**builtins_selector.c
*/
int						search_for_builtins(t_ult *ult);

/*
**free_procjob.c
*/
void					destroy_proc_one(t_process *proc);
void					destroy_proc_list(t_process *proc_list);
void					destroy_job_one(t_job *job);
void					destroy_job_list(t_job *job_list);

#endif
