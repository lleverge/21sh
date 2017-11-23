/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:45:38 by vfrolich          #+#    #+#             */
/*   Updated: 2017/06/22 19:17:43 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstaddend(t_list *alst, t_list *lst)
{
	if (!alst || !lst)
		return ;
	while (alst->next)
		alst = alst->next;
	alst->next = lst;
}
