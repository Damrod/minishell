/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdisplay.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:10:48 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/27 16:12:46 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstdisplay(t_list *list, void (*disp)(void *, int))
{
	int		i;

	if (!(list))
		return ;
	i = 0;
	while (list)
	{
		disp(list->content, i);
		list = list->next;
		i++;
	}
	return ;
}
