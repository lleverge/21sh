/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:16:17 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/18 13:43:00 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int					count_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

char				**ft_tabdup(char **tab)
{
	char	**tab_cpy;
	int		i;

	i = 0;
	if (!(tab_cpy = (char **)malloc(sizeof(char *) * (count_tablen(tab) + 1))))
		exit(1);
	while (tab[i] != 0)
	{
		tab_cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	tab_cpy[i] = 0;
	return (tab_cpy);
}

t_env				*env_cpy(t_env *envtmp, t_env *env)
{
	while (env)
	{
		envtmp = var_cpy(env, envtmp);
		env = env->next;
	}
	return (envtmp);
}

char				*getvarcontent(char *envar)
{
	int		i;
	int		j;
	char	*varcontent;

	i = 0;
	j = 0;
	while (envar[i])
		i++;
	while (envar[j] != '=' && envar[j])
		j++;
	j += 1;
	if (j == i)
		return (NULL);
	else
		varcontent = ft_strsub(envar, j, i);
	return (varcontent);
}

char				*getvarname(char *envar)
{
	int		i;
	int		j;
	char	*varname;

	i = 0;
	j = 0;
	while (envar[i] != '=' && envar[i])
		i++;
	varname = ft_strsub(envar, j, i);
	return (varname);
}
