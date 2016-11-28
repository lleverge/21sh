/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 15:47:06 by lleverge          #+#    #+#             */
/*   Updated: 2015/12/07 17:37:57 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*new;
	t_list	*start;

	new = f(lst);
	tmp = ft_lstnew(new->content, new->content_size);
	start = tmp;
	tmp2 = tmp;
	lst = lst->next;
	while (lst)
	{
		new = f(lst);
		tmp = ft_lstnew(new->content, new->content_size);
		tmp2->next = tmp;
		lst = lst->next;
	}
	return (start);
}
