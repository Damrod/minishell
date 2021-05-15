/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:17:06 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/27 16:17:15 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstmerge(t_list **a, t_list *b)
{
	t_list	*aux;

	if (!b || !a)
		return ;
	if (!*a)
	{
		*a = b;
		return ;
	}
	aux = ft_lstlast(*a);
	aux->next = b;
}
