/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:20:04 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/27 16:20:14 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstsplit(t_list *src, t_list **a, t_list **b)
{
	t_list	*fast;
	t_list	*slow;

	if (!src || !src->next)
		return ;
	slow = src;
	fast = slow->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	*a = src;
	*b = slow->next;
	slow->next = NULL;
}
