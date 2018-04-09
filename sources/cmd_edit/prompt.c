/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:45:54 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/09 18:12:52 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

void			color(char *color, char *str)
{
	ft_putchar_fd('\033', 1);
	ft_putstr_fd(color, 1);
	ft_putstr_fd(str, 1);
}

static void		prompt_path(int i, char *buff)
{
	char	*str;

	if (i >= 1)
	{
		color(PURPLE, "");
		ft_putchar('~');
		color(RESET, "");
	}
	if (i > 1)
	{
		str = ft_strdup(&buff[i]);
		color(PURPLE, str);
		color(RESET, "");
		free(str);
	}
	else if (i == 0)
	{
		str = ft_strdup(ft_strchr(buff, '/'));
		color(PURPLE, str);
		color(RESET, "");
		free(str);
	}
	ft_putchar('\n');
}

static void		prompt_name(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strcmp(env->name, "USER") == 0)
		{
			color(CYAN, env->content);
			color(RESET, "");
		}
		env = env->next;
	}
	env = tmp;
	ft_putstr(" in ");
}

static int		pwd_home(t_env *env, char *buff)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
		{
			if (ft_strchr(env->content, '/') &&
			ft_strcmp(ft_strchr(env->content, '/'), buff) == 0)
				return (1);
			else if (ft_strncmp(ft_strchr(env->content, '/'), buff,
								ft_strlen(ft_strchr(env->content, '/'))) == 0)
			{
				i = ft_strlen(ft_strchr(env->content, '/'));
				return (i);
			}
		}
		env = env->next;
	}
	env = tmp;
	return (0);
}

void			get_prompt(t_env *env)
{
	char	buff[100];
	int		i;

	color(BLUE, "# ");
	color(RESET, "");
	prompt_name(env);
	ft_bzero(buff, 100);
	if (get_intel(env, "PWD") == 1)
	{
		getcwd(buff, 100);
		if (buff[0] != 0)
		{
			i = pwd_home(env, buff);
			prompt_path(i, buff);
		}
		else
			ft_putendl_fd("\033[31mDirectory does not exist\033[39m", 2);
	}
}
