/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:09:23 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/27 17:11:19 by vfrolich         ###   ########.fr       */
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
# include <fcntl.h>

# define RED "[31m"
# define PURPLE "[1;35m"
# define GREEN "[32m"
# define CYAN "[0;36m"
# define BLUE "[1;34m"
# define RESET "[39m"

# define LDNEXT tmp->next->next
# define LNEXT tmp->next
# define LPREV tmp->prev

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

typedef struct			s_close
{
	int					fd;
	struct s_close		*next;
}						t_close;

typedef struct			s_process
{
	int					token_id;
	char				*cmd;
	int					fd[3];
	pid_t				pid;
	int					done;
	t_close				*fd_to_close;
	struct s_process	*next;
}						t_process;

typedef struct			s_job
{
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

typedef struct			s_quote
{
	int					quotes[2];
	struct s_quote		*next;
}						t_quote;

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
int						reset_term(t_term *termi);

/*
**init_job.c
*/
t_job					*job_list(t_job *job, char *cmd);
void					job_pushb(t_job **head, t_job *new);
t_job					*create_job_node(t_process *cmd);

/*
**init_process.c
*/
t_close					*close_init(int fd);
t_process				*process_list(t_process *proc, char *cmd);
void					proc_pushb(t_process **head, t_process *new);
t_process				*create_proc_node(char *cmd, int token_id);
t_process				*stock_proc(t_process *proc, int i);

/*
**init_hist.c
*/
t_hist					*init_hist(t_hist *hist);

/*
**safe_term_init.c
*/
void					safe_term_boot(void);
void					tcaps_check(void);

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
int						is_cmd_empty(char *cmd);
char					*get_data(t_env *env, char *ref_name);
char					*copy_cmd(char *cmd);

/*
**display_tools.c
*/
void					soft_re_prompt(t_ult *ult);
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
int						is_simple_redir(char *cmd);
int						is_redir_append(char *cmd);
int						is_fildes_agreg(char *cmd);
int						is_input_redir(char *cmd);
int						is_heredoc(char *cmd);
t_quote					*quoted_list_init_one(char *sub_cmd, char *cmd);
t_quote					*quote_list_init(char *cmd);
int						is_quoted(char *cmd, int index);
void					quote_extracter(char *cmd, int *i);
int						get_wordlen(char *sub_cmd);

/*
**redir_tools_c.c
*/
char					*fd_to_atoi(char *sub_cmd);

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
int						exe_fork2(t_env *env, t_process *proc,
								t_ult *ult, int fd[2]);
int						exe_fork(t_env *env, t_process *proc,
								t_ult *ult, int fd[2]);
void					exe_clean(t_process *proc, char **env_cpy,
								char **cmd_tab);

/*
**fork2.c
*/
void					fork_error(char **cmd, char **path_tab);
char					*search_path2(char *tmp2, char *tmp, char **path_tab,
							int i);
void					fork_setup(t_process *proc, t_ult *ult, int fd[2]);

/*
**manage_fd.c
*/
void					set_fd_exec(t_process *proc);
void					close_fd_exec(t_process *proc);
void					restore_fd(int fd[3]);

/*
**tools2.c
*/
int						list_size(t_env *env);
int						path_access_checker(char *cmd_path);

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
**safe_position_tools.c
*/
char					*get_cdir(t_env *env);

/*
**builtins_selector.c
*/
int						search_for_builtins(t_ult *ult, t_process *proc);
int						check_for_builtin(char *cmd);

/*
**free_procjob.c
*/
void					destroy_proc_one(t_process *proc);
void					destroy_proc_list(t_process *proc_list);
void					destroy_job_one(t_job *job);
void					destroy_job_list(t_job *job_list);

/*
**main_redirection.c
*/
t_process				*main_redirection_checker(t_process *proc, t_ult *ult);

/*
**is_blankword.c
*/
int						is_blankword(char *str);

/*
**apply_redirect.c
*/
t_job					*apply_redirect(t_job *job_li, t_ult *ult);

/*
**job_launch.c
*/
void					job_launch(t_job *job_li, t_ult *ult);
void					proc_launch(t_process *proc, t_ult *ult, int fd[2]);

/*
**wait_procs.c
*/
void					wait_for_procs(t_process *procs);
#endif
