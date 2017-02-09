/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:20:35 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/09 15:41:24 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

t_prompt		*init_prompt(void)
{
	t_prompt	*prom;

	if (!(prom = (t_prompt *)malloc(sizeof(t_prompt))))
		return (NULL);
	prom->len = 0;
	return (prom);
}
