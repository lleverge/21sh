/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quoted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:42:27 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/12 18:37:17 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int 		first_quote(char *sub_cmd, char *cmd)
{
	int 		quote;
	int 		dquote;

	quote = 0;
	dquote = 0;
	if (!ft_strchr(sub_cmd, '"'))
		return (ft_strchr(cmd, '\'') - cmd);
	if (!ft_strchr(sub_cmd, '\''))
		return (ft_strchr(cmd, '"') - cmd);
	quote = ft_strchr(sub_cmd, '\'') - cmd;
	dquote = ft_strchr(sub_cmd, '"') - cmd;
	return (dquote < quote ? dquote : quote);
}

static	int		endquote(char *cmd, int firstquote)
{
	char 		*sub_cmd;
	char 		delim;

	sub_cmd = &cmd[firstquote];
	delim = *sub_cmd;
	sub_cmd++;
	return (ft_strchr(sub_cmd, delim) - cmd);
}

t_quote 		*quoted_list_init_one(char *sub_cmd, char *cmd)
{
	t_quote 	*new;

	if (!(new = (t_quote *)malloc(sizeof(t_quote))))
		return (NULL);
	new->quotes[0] = first_quote(sub_cmd, cmd);
	new->quotes[1] = endquote(cmd, new->quotes[0]);
	new->next = NULL;
	return (new);
}

static void		quote_destroy(t_quote *quote_list)
{
	t_quote	*tmp;

	while (quote_list)
	{
		tmp = quote_list->next;
		free(quote_list);
		quote_list = tmp;
	}
	quote_list = NULL;
}

int		is_quoted(char *cmd, int index)
{
	t_quote *quotelist;
	t_quote	*tmplist;

	if (!ft_strchr(cmd, '"') && !ft_strchr(cmd, '\''))
		return (0);
	quotelist = quote_list_init(cmd);
	tmplist = quotelist;
	while (tmplist)
	{
		if (index >= tmplist->quotes[0] && index <= tmplist->quotes[1])
			return (1);
		tmplist = tmplist->next;
	}
	quote_destroy(quotelist);
	return (0);
}
