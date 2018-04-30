# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/21 17:32:58 by lleverge          #+#    #+#              #
#    Updated: 2018/04/30 11:40:48 by vfrolich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 21sh
SRC		= sources/auto_complete/exec_more.c\
	sources/auto_complete/free_tools.c\
	sources/auto_complete/print_compl.c\
	sources/auto_complete/print_tools.c\
	sources/auto_complete/read_compl.c\
	sources/auto_complete/select_actions.c\
	sources/auto_complete/select_return.c\
	sources/auto_complete/small_prompt.c\
	sources/auto_complete/word_detect.c\
	sources/builtins/builtins_selector.c\
	sources/builtins/cd.c\
	sources/builtins/cd_2.c\
	sources/builtins/echo.c\
	sources/builtins/env.c\
	sources/builtins/env2.c\
	sources/builtins/env_builtin_tools.c\
	sources/builtins/exit.c\
	sources/builtins/setenv.c\
	sources/builtins/unsetenv.c\
	sources/builtins/setunsetenv.c\
	sources/builtins/setting_tmp_ult.c\
	sources/cmd_edit/cut.c\
	sources/cmd_edit/edit_tools.c\
	sources/cmd_edit/heredoc_prompt.c\
	sources/cmd_edit/hist.c\
	sources/cmd_edit/homend.c\
	sources/cmd_edit/insert.c\
	sources/cmd_edit/insert2.c\
	sources/cmd_edit/main_auto.c\
	sources/cmd_edit/term_setup.c\
	sources/cmd_edit/move.c\
	sources/cmd_edit/prompt.c\
	sources/cmd_edit/tcaps.c\
	sources/cmd_edit/updown.c\
	sources/exec/apply_redirect.c\
	sources/exec/error.c\
	sources/exec/fork.c\
	sources/exec/fork2.c\
	sources/exec/hash_table.c\
	sources/exec/hash_table2.c\
	sources/exec/hash_tools.c\
	sources/exec/job_launch.c\
	sources/exec/manage_fd.c\
	sources/exec/signal.c\
	sources/exec/tools2.c\
	sources/exec/tools3.c\
	sources/exec/wait_procs.c\
	sources/init_file/init_complete.c\
	sources/init_file/init_complete2.c\
	sources/init_file/init_complete3.c\
	sources/init_file/init_env.c\
	sources/init_file/init_hist.c\
	sources/init_file/init_job.c\
	sources/init_file/init_process.c\
	sources/init_file/init_prompt.c\
	sources/init_file/init_term.c\
	sources/init_file/init_tools.c\
	sources/init_file/init_ult.c\
	sources/init_file/safe_term_init.c\
	sources/lexer/free_procjob.c\
	sources/lexer/lexer.c\
	sources/lexer/lexer_to_str.c\
	sources/lexer/lexer2.c\
	sources/lexer/format_arg.c\
	sources/lexer/format_arg_2.c\
	sources/lexer/merge_quotes.c\
	sources/lexer/init_lexproc.c\
	sources/lexer/new_lexer.c\
	sources/lexer/pipe_prompt.c\
	sources/lexer/quote_prompt.c\
	sources/lexer/quote_handler.c\
	sources/lexer/quote_handler_2.c\
	sources/lexer/seek_exec.c\
	sources/lexer/token_list.c\
	sources/lexer/token_recognizer.c\
	sources/lexer/is_dquoted.c\
	sources/lexer/expand_var.c\
	sources/lexer/cut_shellvar.c\
	sources/lexer/apply_expand.c\
	sources/main.c\
	sources/parse_error/parse_error.c\
	sources/parse_error/parse_error2.c\
	sources/parse_error/parse_errortools.c\
	sources/redirection/filedes_agreg.c\
	sources/redirection/filedes_agreg_epur.c\
	sources/redirection/ft_isbadtoken.c\
	sources/redirection/heredoc.c\
	sources/redirection/heredoc2.c\
	sources/redirection/heredoc_signal.c\
	sources/redirection/is_quoted.c\
	sources/redirection/main_redirection.c\
	sources/redirection/quote_list_init.c\
	sources/redirection/redir_append.c\
	sources/redirection/redir_detect.c\
	sources/redirection/redir_input.c\
	sources/redirection/redir_tools.c\
	sources/redirection/redir_tools_2.c\
	sources/redirection/redirect_fd.c\
	sources/redirection/quote_cut_handle.c\
	sources/tools/cmd_tools.c\
	sources/tools/display_tools.c\
	sources/tools/env_tools.c\
	sources/tools/free_tools.c\
	sources/tools/ft_strsplit_tok.c\
	sources/tools/ft_strsplit_ws.c\
	sources/tools/is_blankword.c\
	sources/tools/prompt_tools.c\
	sources/tools/expand_tools.c\
	sources/tools/safe_position_tools.c

OBJ 	= $(SRC:.c=.o)
FLAGS	= -Wall -Werror -Wextra
LIB		= -L./libft -lft -ltermcap

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Creating $(NAME)"
	@make -C ./libft
	@gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

%.o: %.c
	@echo "Creating object : $@"
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@echo "Deleting objects"
	@rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@echo "Deleting $(NAME)"
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re