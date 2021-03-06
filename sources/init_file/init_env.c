/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:08:42 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/16 14:58:38 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

t_env				*var_cpy(t_env *start, t_env *cpy)
{
	t_env	*tmp;
	t_env	*voyager;
	t_ult	*ult;

	tmp = NULL;
	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
	{
		ft_putendl_fd("21sh : allocation error, abort.", 2);
		exit_term(ult->term);
		exit(3);
	}
	voyager = cpy;
	tmp->name = ft_strdup(start->name);
	tmp->content = ft_strdup(start->content);
	tmp->next = NULL;
	if (voyager == NULL)
		return (tmp);
	while (voyager->next)
		voyager = voyager->next;
	voyager->next = tmp;
	return (cpy);
}

t_env				*env_in_list(char *envar, t_env *start)
{
	t_env	*tmp;
	t_env	*voyager;
	t_ult	*ult;

	tmp = NULL;
	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
	{
		ft_putendl_fd("21sh : allocation error, abort.", 2);
		exit_term(ult->term);
		exit(3);
	}
	tmp->next = NULL;
	voyager = start;
	tmp->name = getvarname(envar);
	tmp->content = getvarcontent(envar);
	if (start == NULL)
		return (tmp);
	while (voyager->next)
		voyager = voyager->next;
	voyager->next = tmp;
	return (start);
}

t_env				*fill_env(char **environ)
{
	t_env		*env;
	char		**envi;
	int			i;

	i = -1;
	envi = ft_tabdup(environ);
	env = NULL;
	while (envi[++i] != 0)
		env = env_in_list(envi[i], env);
	free_tab(envi);
	return (env);
}
