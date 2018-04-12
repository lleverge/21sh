/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbadtoken.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:06:07 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/12 15:58:55 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		ft_isbadtoken(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
}
