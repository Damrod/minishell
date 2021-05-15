/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 19:58:31 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/05 15:51:30 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!(lst) || !(new))
		return ;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
	return ;
}
