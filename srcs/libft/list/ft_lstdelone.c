/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:05:45 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 10:40:44 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstdelone(t_list *lst, void (*delcnt)(void *), void (*delnde)(void*))
{
	if (!lst)
		return ;
	if (delcnt)
		delcnt(lst->content);
	if (delnde)
		delnde(lst);
	return ;
}
