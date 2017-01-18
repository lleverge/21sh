/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 09:55:27 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/18 09:55:30 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_node			*init_node(void)
{
	t_node		*new;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	new->token_id = 0;
	new->content = NULL;
	new->cmd = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
