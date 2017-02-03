/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 18:25:57 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/25 18:28:33 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

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
