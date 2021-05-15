/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 21:42:22 by aollero-          #+#    #+#             */
/*   Updated: 2020/07/01 21:46:19 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !(f))
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
	return ;
}
