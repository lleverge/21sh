/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 12:01:29 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/12 16:06:07 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

char	*ft_getbin_path(char *cmd)
{
	int		count;
	char	*path;
	int		i;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			count = i;
		i++;
	}
	if (count > 0)
	{
		path = ft_strsub(cmd, 0, count);
		return (path);
	}
	else
		return (NULL);
}

char	*ft_getbin_name(char *cmd)
{
	int		count;
	char	*name;
	int		i;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			count = i;
		i++;
	}
	if (count != 0)
		name = ft_strsub(cmd, count + 1, ft_strlen(cmd));
	else
		name = ft_strsub(cmd, count, ft_strlen(cmd));
	return (name);
}

char	**ft_tabdup_path(char **tab, char *content)
{
	char	**tab_cpy;
	int		i;

	i = 0;
	if (content)
	{
		if (!(tab_cpy = (char **)malloc(sizeof(char *)
										* (count_tablen(tab) + 2))))
			exit(1);
		while (tab[i] != 0)
		{
			tab_cpy[i] = ft_strdup(tab[i]);
			i++;
		}
		tab_cpy[i] = ft_strdup(content);
		free_tab(tab);
		return (tab_cpy);
	}
	else
		return (tab);
}

char	**part_tabcpy(char **tab)
{
	int		i;
	int		j;
	int		count;
	char	**new;

	i = 2;
	j = 0;
	count = 0;
	while (tab[i] != 0)
	{
		count++;
		i++;
	}
	if (!(new = (char **)malloc(sizeof(char *) * count + 1)))
		return (NULL);
	i = 2;
	while (tab[i] != 0)
	{
		new[j] = ft_strdup(tab[i]);
		j++;
		i++;
	}
	new[j] = NULL;
	return (new);
}

char	**list_in_tab(t_env *env)
{
	int		size;
	char	*str;
	char	*tmp;
	char	**envir;
	int		i;

	i = 0;
	size = list_size(env);
	if (!(envir = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		str = ft_strjoin_free_one(&tmp, env->content);
		ft_strdel(&tmp);
		envir[i] = str;
		i++;
		env = env->next;
	}
	envir[i] = 0;
	return (envir);
}
