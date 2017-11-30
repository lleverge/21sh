/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:58:32 by lleverge          #+#    #+#             */
/*   Updated: 2017/10/26 18:55:05 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

char			*last_proc(char *cmd)
{
	int		len;
	int		i;

	len = ft_strlen(cmd);
	i = len;
	while (!ft_istoken(cmd[i]))
		i--;
	return (ft_strsub(cmd, i + 1, len - i));
}

void			prep_proc(t_process **proc_li, char *str)
{
	size_t		i;
	t_process	*new;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (ft_istoken(str[i]) == 3)
		{
			new = create_proc_node(new, str);
			proc_pushb(proc_li, prep_pipe(new, str, i));
		}
		else if (i == ft_strlen(str) - 1)
		{
			new = create_proc_node(new, str);
			proc_pushb(proc_li, prep_pipe(new, str, i));
			new->token_id = SEPARATOR;
		}
		i++;
	}
}

t_process		*prep_pipe(t_process *new, char *str, int i)
{
	int		j;

	j = i - 1;
	new->token_id = PIPE;
	while (j != 0 && str[j] != '|')
		j--;
	if (j != 0)
		j += 1;
	new->cmd = ft_strsub(str, j, i - j);
	ft_putendl(new->cmd);
	return (new);
}
