/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:10:54 by lleverge          #+#    #+#             */
/*   Updated: 2017/12/14 19:17:25 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

static char		*cpy_at(char *src1, char *src2, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*res;

	if (ft_strcmp(src1, "") == 0)
	{
		tmp = ft_strdup(src2);
		return (tmp);
	}
	else if (src1 && src2)
	{
		tmp = ft_strsub(src1, 0, i);
		tmp2 = ft_strjoin(tmp, src2);
		ft_strdel(&tmp);
		tmp = ft_strsub(src1, i, ft_strlen(src1));
		res = ft_strjoin(tmp2, tmp);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		return (res);
	}
	else
	{
		return (NULL);
	}
}

void			copy(t_prompt *prompt, char *buffer, int i)
{
	if (T_CPY)
	{
		if (prompt->copy_str)
			ft_strdel(&(prompt->copy_str));
		prompt->copy_mode = 1;
		prompt->copy_str = ft_strsub(prompt->cmd, i,
									ft_strlen(prompt->cmd) - i);
	}
}

void			cut(t_prompt *prompt, char *buffer, int i)
{
	char	*tmp;
	char	*tmp2;

	if (T_CUT)
	{
		if (prompt->copy_str)
			ft_strdel(&(prompt->copy_str));
		prompt->copy_mode = 1;
		tmp = ft_strsub(prompt->cmd, i, ft_strlen(prompt->cmd) - i);
		tmp2 = ft_strsub(prompt->cmd, 0, i);
		prompt->copy_str = ft_strdup(tmp);
		ft_bzero(prompt->cmd, 2000);
		ft_memcpy(prompt->cmd, tmp2, ft_strlen(tmp2));
		ft_strdel(&tmp2);
		ft_strdel(&tmp);
		print_backsp(prompt, 1);
	}
}

void			paste(t_prompt *prompt, char *buffer)
{
	char	*tmp;
	int		itmp;
	size_t		j;
	size_t		k;

	j = 3;
	k = 0;
	if (T_PAS && prompt->copy_str)
	{
		itmp = prompt->i;
		tmp = cpy_at(prompt->cmd, prompt->copy_str, prompt->i);
		prompt->i += ft_strlen(prompt->copy_str);
		if (prompt->i <= 2000)
		{
			ft_bzero(prompt->cmd, 2000);
			ft_memcpy(prompt->cmd, tmp, ft_strlen(tmp));
		}
		else
			prompt->i = itmp;
		ft_strdel(&tmp);
		print_backsp(prompt, 1);
	}
}
