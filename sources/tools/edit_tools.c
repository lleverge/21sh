/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 18:25:57 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/01 12:50:42 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

void		supress_end(t_edit *ed)
{
	ft_putchar(' ');
	use_ncap("nd", ed->termi->ws.ws_col - 1);
}

char		*ft_strsupress_at(char *str, size_t pos)
{
	char	*ret;
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(str))))
	{
		ft_putendl_fd("error: strsupress_at malloc failed", 2);
		exit(-1);
	}
	tmp = ft_strncpy(tmp, str, pos);
	pos++;
	while (*str && pos--)
		str++;
	ret = ft_strjoin(tmp, str);
	free(tmp);
	return (ret);
}

int			check_max(t_edit *ed, t_cursor *curs, char *cmd_line, int index)
{
	if ((cursor_to_sbuffer(ed, curs->x, curs->y) -
		ed->input->lprom + index) == (int)ft_strlen(cmd_line))
		return (1);
	else
		return (0);
}

void		use_ncap(char *cap, int n)
{
	char	*res;
	int		i;

	i = 0;
	while (i <= n)
	{
		if ((res = tgetstr(cap, NULL)) == NULL)
		{
			ft_putendl_fd("The cap doesn't exist", 2);
			exit(-1);
		}
		ft_putstr(res);
		i++;
	}
}

void		use_cap(char *cap)
{
	char	*res;

	if ((res = tgetstr(cap, NULL)) == NULL)
	{
		ft_putendl_fd("The cap doesn't exist\n", 2);
		exit(-1);
	}
	ft_putstr(res);
}
