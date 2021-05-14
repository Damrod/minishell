/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 21:08:13 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 10:40:28 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*delcnt)(void*), void (*delnde)(void*))
{
	t_list	*tmp;
	t_list	**head;

	head = lst;
	if (!(lst) || !(*lst))
		return ;
	tmp = *lst;
	while (tmp)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, delcnt, delnde);
		(*lst) = tmp;
	}
	if (delnde)
		delnde(*head);
	return ;
}
