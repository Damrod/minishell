/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:16:08 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/27 16:16:14 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstpop_back(t_list **lst)
{
	t_list	*aux1;
	t_list	*aux2;

	if (!lst || !*lst)
		return (NULL);
	aux2 = *lst;
	while (aux2->next && aux2->next->next)
		aux2 = aux2->next;
	if (aux2->next)
	{
		aux1 = aux2->next;
		aux2->next = NULL;
	}
	else
	{
		aux1 = aux2;
		*lst = NULL;
	}
	return (aux1);
}
