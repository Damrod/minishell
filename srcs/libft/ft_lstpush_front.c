/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:13:45 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/27 16:14:00 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush_front(t_list **lst, void *content)
{
	t_list	*aux;

	aux = ft_lstnew(content);
	if (!aux)
		return ;
	ft_lstadd_front(lst, aux);
}
