/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexproc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 22:29:44 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/18 19:39:06 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexer.h"

t_lexer			*lex_from_proc(t_process *proc)
{
	t_lexer		*dest;

	dest = init_lexer(proc->cmd);
	return (dest);
}
