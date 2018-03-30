/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:48:19 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/30 15:55:28 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <lexer.h>

char			*word_array_to_str(char **args_arr)
{
	char	**tmp;
	char	*dest;

	dest = NULL;
	tmp = args_arr;
	if (**tmp == '-')
		tmp++;
	while (*tmp && ft_strchr(*tmp, '='))
		tmp++;
	if (*tmp)
	{
		dest = ft_strdup(*tmp);
		dest = ft_strjoin_free_one(&dest, " ");
		tmp++;
	}
	while (*tmp)
	{
		dest = ft_strjoin_free_one(&dest, *tmp);
		dest = ft_strjoin_free_one(&dest, " ");
		tmp++;
	}
	return (dest);
}

t_lexer			*fill_lexer_env(t_ult *ult, char *cmd)
{
	t_lexer		*lexlist;

	lexlist = init_lexer(cmd);
	if (!(lexlist = quote_tok(lexlist, ult)))
		return (NULL);
	lexlist = merge_token(lexlist);
	lexlist = prompt_pipe(lexlist, ult);
	lexlist = quote_tok(lexlist, ult);
	if (!(lexlist = quote_tok(lexlist, ult)))
		return (NULL);
	lexlist = merge_token(lexlist);
	if (parse_error(lexlist, ult->fd[2]) == -1)
		return (NULL);
	return (lexlist);
}

t_ult			*setting_tmp_ult(t_ult *ult, t_env *env)
{
	t_ult		*dest;

	dest = NULL;
	if (!(dest = (t_ult *)malloc(sizeof(t_ult))))
	{
		ft_putendl_fd("error: ult struct malloc failed", 2);
		exit(-1);
	}
	dest->env = env;
	if (!env)
		dest->hash_table = NULL;
	else
		dest->hash_table = table_init(env);
	dest->fd[0] = ult->fd[0];
	dest->fd[1] = ult->fd[1];
	dest->fd[2] = ult->fd[2];
	dest->term = ult->term;
	return (dest);
}
