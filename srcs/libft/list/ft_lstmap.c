/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 21:49:42 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 13:38:42 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*delcnt)(void *),
					void (*delnde)(void *))
{
	t_list	*resul;
	t_list	*new_head;

	if (!lst || !(delcnt) || !(f))
		return (NULL);
	if (!na_lstnew(f(lst->content), &new_head))
	{
		ft_lstdelone(new_head, delcnt, delnde);
		return (NULL);
	}
	while (lst->next)
	{
		if (!na_lstnew(f(lst->next->content), &resul))
		{
			ft_lstclear(&new_head, delcnt, delnde);
			return (NULL);
		}
		ft_lstadd_back(&new_head, resul);
		lst = lst->next;
	}
	return (new_head);
}
