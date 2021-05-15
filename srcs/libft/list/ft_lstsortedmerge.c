/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_lst_merge.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:18:30 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/27 16:59:08 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_sorted_merge2(t_list **a, t_list *b, int (*cmp)(), t_list *ind)
{
	while (1)
	{
		if (!b || !*a)
		{
			if (!b)
				ind->next = *a;
			if (!*a)
				ind->next = b;
			break ;
		}
		if (cmp((*a)->content, b->content) > 0)
			ft_lstadd_front(&(ind->next), ft_lstpop_front(&b));
		else
			ft_lstadd_front(&(ind->next), ft_lstpop_front(a));
		ind = ind->next;
	}
}

void	ft_sorted_lst_merge(t_list **a, t_list *b, int (*cmp)())
{
	t_list	*indirect;
	t_list	aux;

	if (!b || !a)
		return ;
	if (!*a)
	{
		*a = b;
		return ;
	}
	aux.next = NULL;
	indirect = &aux;
	ft_sorted_merge2(a, b, cmp, indirect);
	*a = aux.next;
}
