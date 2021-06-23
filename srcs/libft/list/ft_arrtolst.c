/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrtolst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:08:42 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 11:19:44 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_arrtolst(void **array, int size, void *(*alloc)())
{
	t_list	*list;

	if (size < 0)
		size = ft_dblptrlen(array);
	list = NULL;
	while (size)
	{
		if (alloc)
			ft_lstadd_front(&list, alloc(ft_lstnew(array[size - 1])));
		else
			ft_lstadd_front(&list, ft_lstnew(array[size - 1]));
		size--;
	}
	return (list);
}
