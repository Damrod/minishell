/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:14:39 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/27 16:14:57 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstpush_back(t_list **lst, void *content)
{
	t_list	*aux;

	if (!content)
		return ;
	aux = ft_lstnew(content);
	if (!aux)
		return ;
	ft_lstadd_back(lst, aux);
}
