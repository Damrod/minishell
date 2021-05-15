/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:15:20 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/27 16:15:33 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstpop_front(t_list **lst)
{
	t_list	*aux1;

	if (!lst || !*lst)
		return (NULL);
	aux1 = *lst;
	*lst = aux1->next;
	aux1->next = NULL;
	return (aux1);
}
