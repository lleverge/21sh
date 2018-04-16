/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 11:36:02 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/16 15:45:43 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

t_env		*envlist_cpy(t_env *src)
{
	t_env	*new;
	t_ult	*ult;

	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!src)
		return (NULL);
	if (!(new = (t_env *)malloc(sizeof(t_env))))
	{
		ft_putendl_fd("21sh : allocation error, abort.", 2);
		exit_term(ult->term);
		exit(3);
	}
	new->name = ft_strdup(src->name);
	new->content = ft_strdup(src->content);
	new->next = envlist_cpy(src->next);
	return (new);
}

int			index_start_newtab(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] && *cmd[i] == '-')
		i++;
	while (cmd[i] && ft_strchr(cmd[i], '='))
		i++;
	return (i);
}

int			check_opt(char *opt)
{
	if (*opt != '-')
		return (2);
	if (opt[1] && opt[1] == 'i')
		return (0);
	else if (opt[1])
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(opt[1], 2);
		ft_putchar_fd('\n', 2);
		ft_putendl_fd("usage : env [-i] [name=value ...] [utility [argument .\
..]]", 2);
	}
	return (1);
}

static int	count_strings(char **src, int index_start_newtab)
{
	char	**tmp;
	int		index;

	tmp = &src[index_start_newtab];
	index = 0;
	while (*tmp)
	{
		index++;
		tmp++;
	}
	return (index);
}

char		**tab_dup(char **src, int index_start_newtab)
{
	char	**dest;
	char	**tmp;
	int		index;
	t_ult	*ult;

	dest = NULL;
	ult = NULL;
	ult = stock_ult(ult, 1);
	index = count_strings(src, index_start_newtab);
	if (!(dest = (char **)malloc(sizeof(char *) * (index + 1))))
	{
		ft_putendl_fd("21sh allocation error, abort.", 2);
		exit_term(ult->term);
		exit(3);
	}
	dest[index] = NULL;
	tmp = &src[index_start_newtab];
	index = 0;
	while (*tmp)
	{
		dest[index] = ft_strdup(*tmp);
		tmp++;
		index++;
	}
	return (dest);
}
