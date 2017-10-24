/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:58:32 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/24 13:09:55 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

t_process		*prep_pipe(t_process *new, char *str, int i)
{
	int		j;

	j = i - 1;
	new->token_id = PIPE;
	while (j == 0 || j != '|')
		j--;
	new->cmd = ft_strsub(str, j, i - 1 - j);
	ft_putendl(new->cmd);
	return (new);
}
