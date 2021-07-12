/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit_half.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:20:04 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/27 16:20:14 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstsplit_half(t_list *src, t_list **a, t_list **b)
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

t_list	*ft_lstsplit_at(t_list *s, t_list **b, void *key, int (*cmp)())
{
	if (!s || !b)
		return (NULL);
	*b = NULL;
	while (s->next)
	{
		if (!cmp(s->content, key))
		{
			*b = s->next;
			s->next = NULL;
			break ;
		}
		s = s->next;
	}
	return (*b);
}

t_dlist	*ft_lstsplit(t_list *src, void *key, int (*cmp)())
{
	t_list	*head;
	t_dlist	*lstoflists;

	lstoflists = NULL;
	ft_dlstpush_back(&lstoflists, src);
	head = src;
	while (head)
	{
		ft_dlstpush_back(&lstoflists,
			ft_lstsplit_at(head, &head, key, cmp));
	}
	return (lstoflists);
}
