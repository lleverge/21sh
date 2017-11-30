/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:59:45 by lleverge          #+#    #+#             */
/*   Updated: 2017/11/13 16:13:02 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

void			reset(t_prompt *prompt)
{
	int		i;

	i = prompt->y;
	while (i > 0 && i != 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
		i--;
	}
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
	if (!prompt->heredoc)
	{
		color(RED, "$> ");
		color(RESET, "");
	}
	else
		ft_putstr("> ");
}

static void		lesslines(t_prompt *prompt, t_ult *ult, size_t i)
{
	int		y;

	y = prompt->y;
	if (i == prompt->win_size - 3 || i == prompt->win_size - 4)
	{
		while (y + 1)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar_int);
			y--;
		}
		get_prompt(ult->env);
	}
}

void			reset_prompt2(t_prompt *prompt, t_ult *ult)
{
	size_t		i;
	size_t		j;

	j = 3;
	i = 0;
	tputs(tgetstr("vi", NULL), 1, ft_putchar_int);
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	lesslines(prompt, ult, i);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
	if (prompt->heredoc)
	{
		color(RED, "$> ");
		color(RESET, "");
	}
	else
		ft_putstr("> ");
}

int				ft_putchar_int(int c)
{
	ft_putchar((char)c);
	return (0);
}

int				get_intel(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strcmp(env->name, str) == 0)
		{
			env = tmp;
			return (1);
		}
		env = env->next;
	}
	env = tmp;
	return (0);
}
