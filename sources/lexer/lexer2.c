/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 12:28:37 by lleverge          #+#    #+#             */
/*   Updated: 2018/01/23 15:44:37 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <shell.h>

static t_lexer     *check_merge_aggreg2(t_lexer *lexer)
{
    t_lexer     *voyager;
    t_lexer     *tmp;
    t_lexer     *tmp2;

    voyager = lexer;
    if (voyager->token_id == 12 && voyager->next->token_id == 3 && voyager->next->next
        && voyager->next->next->token_id < 12)
	{
		ft_putendl("21sh: lexer2.c: bad token");
		exit(-1);
	}
    else if (voyager->token_id == 12 && voyager->next->token_id == 3)
    {
        tmp = voyager;
        voyager = voyager->next;
        tmp2 = voyager->next;
        ft_strdel(&tmp->content);
        tmp->content = ft_strdup("&>");
        tmp->token_id = 11;
        tmp->next = tmp2;
        tmp2->prev = tmp;
        free_lexer(&voyager);
		lexer = tmp;
        return (lexer);
    }
    else
        return (lexer);
}

static t_lexer     *check_merge_aggreg1(t_lexer *lexer)
{
    t_lexer     *voyager;
    t_lexer     *tmp;
    t_lexer     *tmp2;

    voyager = lexer;
    if (voyager->token_id == 3 && voyager->next->token_id == 12 && voyager->next->next
        && voyager->next->next->token_id < 13)
 	{
		ft_putendl("21sh: lexer2.c: bad token");
		exit(-1);
	}
    else if (voyager->token_id == 3 && voyager->next->token_id == 12)
    {
        tmp = voyager;
        voyager= voyager->next;
        tmp2 = voyager->next;
        ft_strdel(&tmp->content);
        tmp->content = ft_strdup(">&");
        tmp->token_id = 11;
        tmp->next = tmp2;
        tmp2->prev = tmp;
        free_lexer(&voyager);
		lexer = tmp;
        return (lexer);
    }
    else
        return (lexer);
}

static t_lexer		*check_merge_dgreat(t_lexer *lexer)
{
    t_lexer     *voyager;
    t_lexer     *tmp;
    t_lexer     *tmp2;

    voyager = lexer;
    if (voyager->token_id == 3 && voyager->next->token_id == 3 && voyager->next->next
		&& voyager->next->next->token_id < 13)
	{
		ft_putendl("21sh: lexer2.c: bad token");
		exit(-1);
	}
    else if (voyager->token_id == 3 && voyager->next->token_id == 3)
    {
		tmp = voyager;
		voyager = voyager->next;
		tmp2 = voyager->next;
		ft_strdel(&tmp->content);
		tmp->content = ft_strdup(">>");
		tmp->token_id = 4;
		tmp->next = tmp2;
		tmp2->prev = tmp;
		free_lexer(&voyager);
		lexer = tmp;
		return (lexer);
    }
    else
		return (lexer);
}

static t_lexer		*check_merge_dless(t_lexer *lexer)
{
	t_lexer		*voyager;
	t_lexer		*tmp2;

	voyager = lexer;
	if (voyager->token_id == 2 && voyager->next->token_id == 2 && voyager->next->next
		&& voyager->next->next->token_id < 13)
	{
		ft_putendl("21sh: lexer2.c: bad token");
		exit(-1);
	}
	else if (voyager->token_id == 2 && voyager->next->token_id == 2)
	{
		voyager = voyager->next;
		tmp2 = voyager->next;
		ft_strdel(&(lexer->content));
		lexer->content = ft_strdup("<<");
		lexer->token_id = 5;
		lexer->next = tmp2;
		tmp2->prev = lexer;
		free_lexer(&voyager);
		return (lexer);
	}
	else
		return (lexer);
}

void			group_token(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp)
	{
		if (tmp->token_id == 2 && tmp->next && tmp->next->token_id == 2)
			tmp = check_merge_dless(tmp);
		else if (tmp->token_id == 3 && tmp->next && tmp->next->token_id == 3)
			tmp = check_merge_dgreat(tmp);
		else if (tmp->token_id == 3 && tmp->next && tmp->next->token_id == 12)
			tmp = check_merge_aggreg1(tmp);
		else if (tmp->token_id == 12 && tmp->next && tmp->next->token_id == 3)
			tmp = check_merge_aggreg2(tmp);
		tmp = tmp->next;
	}
}
