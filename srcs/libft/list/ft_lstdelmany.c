/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelmany.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 09:29:09 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 11:05:27 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "ft_lstdelmany.h"

static void	lstdelmny(t_list **lst, int (*comp)(), t_delfunct *del, void *param)
{
	t_list	**indirect;
	t_list	*deleted;

	if (!*lst)
		return ;
	indirect = lst;
	while (*indirect)
	{
		while (*indirect && comp((*indirect)->content, param))
		{
			deleted = *indirect;
			*indirect = (*indirect)->next;
			ft_lstdelone(deleted, del->delcont, del->delnode);
		}
		if (*indirect)
			indirect = &((*indirect)->next);
	}
	return ;
}

void	ft_lstdelmany(t_list **lst, int (*cm)(), void (*del)(void *), void *p)
{
	t_delfunct	delfunct;

	delfunct.delcont = del;
	delfunct.delnode = del;
	lstdelmny(lst, cm, &delfunct, p);
}
