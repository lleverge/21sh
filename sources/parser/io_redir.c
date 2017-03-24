/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:03:31 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/24 17:10:45 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

void			open_redir(t_ult *ult, t_lexer *lex)
{
	int		flag;

	flag = O_CREAT | O_WRONLY;
	if (lex->token_id == GREAT)
		flag |= O_TRUNC;
	else if (lex->token_id == DGREAT)
		flag |= O_APPEND;
	if (lex->next->cmd[0])
	{
		if ((ult->exec->fd_write = open(lex->next->cmd[0], flag, 0644)) == -1)
		{
			ft_putendl_fd("42sh: permission denied", 2);
			ult->ret = 1;
		}
		else
			ult->ret = 0;
	}
}

int				fd_len(char *str, int i)
{
	int len;

	len = 0;
	while (ft_isdigit(str[i]))
	{
		i++;
		len++;
	}
	return (len);
}
