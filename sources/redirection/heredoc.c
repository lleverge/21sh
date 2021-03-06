/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 15:52:23 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/27 14:40:18 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"
#include "../../includes/cmd_edit.h"

char			*read_heredoc(t_prompt *prompt, t_ult *ult, int *sig_flag)
{
	static char	buffer[4];

	ft_bzero(buffer, 4);
	signal(SIGINT, &sig_handler_heredoc);
	while (read(0, buffer, 4) != -1 && *sig_flag == 42)
	{
		prompt_shell(prompt, buffer, ult);
		if (buffer[0] == 4 && !prompt->cmd[0])
		{
			reset_prompt_heredoc(prompt, 1);
			tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
			tputs(tgetstr("ce", NULL), 1, ft_putchar_int);
			return (NULL);
		}
		if (buffer[0] == 10 && buffer[1] == 0)
		{
			prompt_print(prompt, 0);
			ft_putchar('\n');
			break ;
		}
		ft_bzero(buffer, 4);
	}
	return (*sig_flag == 42 ? strdup(prompt->cmd) : NULL);
}

static char		*add_nl(char **line)
{
	char		*tmp;
	size_t		w_len;

	w_len = ft_strlen(*line);
	if (!(tmp = (char *)malloc(sizeof(char) * (w_len + 2))))
	{
		ft_putendl_fd("21sh : malloc error", 2);
		exit(1);
	}
	ft_strcpy(tmp, *line);
	tmp[w_len] = '\n';
	tmp[w_len + 1] = '\0';
	ft_strdel(line);
	return (tmp);
}

char			*termcaps_heredoc(t_ult *ult)
{
	t_prompt	*prompt;
	char		*dest;
	int			*flag;

	prompt = init_prompt();
	prompt->heredoc = 1;
	dest = NULL;
	stock_prompt(prompt, 0);
	prompt_print(prompt, 1);
	flag = singleton_signal();
	dest = read_heredoc(prompt, ult, flag);
	*flag = 42;
	dest ? dest = add_nl(&dest) : 0;
	free_prompt(&prompt);
	return (dest);
}

static char		*get_delim(char *cmd)
{
	char		*tmp;

	tmp = ft_strchr(cmd, '<') + 2;
	if (!*tmp)
	{
		ft_putendl_fd("21sh : missing heredoc delimiter", STDERR_FILENO);
		return (NULL);
	}
	tmp = get_word(tmp);
	tmp = add_nl(&tmp);
	return (tmp);
}

t_process		*heredoc(t_process *proc, t_ult *ult)
{
	int			fd[2];
	char		*delim;

	if (pipe(fd) == -1)
	{
		ft_putendl_fd("21sh : pipe error", 2);
		return (NULL);
	}
	if (!(delim = get_delim(proc->cmd)))
		return (NULL);
	stock_ult(ult, 0);
	proc = standard_fd(proc);
	heredoc_write(fd[1], delim, ult);
	if (!proc)
		return (clean_exit_heredoc(fd, &delim));
	if (close(fd[1]) == -1)
	{
		ft_putendl_fd("close error", 2);
		return (NULL);
	}
	proc->fd[0] = fd[0];
	ft_strdel(&delim);
	proc = cmd_epur_heredoc(proc);
	return (proc);
}
