/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 19:32:30 by aollero-          #+#    #+#             */
/*   Updated: 2020/07/26 17:01:23 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*na_lstnew(void *content, t_list **ret_val)
{
	t_list	*list;

	if (!na_malloc(sizeof(*list), (void **) & list))
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (*ret_val = list);
}
