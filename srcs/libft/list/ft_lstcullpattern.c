/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcullpattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:48:43 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 13:42:48 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_lstcullpat(t_list **lst, int *mk, void (*dc)(void *), void (*dn)(void *))
{
	t_list	**indirect;
	int		flag;
	int		sz;
	int		i;
	t_list	*aux;

	sz = 0;
	i = 0;
	indirect = lst;
	while (*indirect)
	{
		flag = 1;
		if (mk[i])
		{
			aux = *indirect;
			*indirect = (*indirect)->next;
			ft_lstdelone(aux, dc, dn);
			sz++;
			flag = 0;
		}
		i++;
		if (flag && *indirect)
			indirect = &(*indirect)->next;
	}
	return (sz);
}

static int	ft_lstdupmask(t_list *list, int *mask, int lstsz)
{
	int		i;
	int		maskidx;
	void	**resul;

	resul = malloc (sizeof(void *) * lstsz);
	if (!resul)
		return (-1);
	i = 0;
	maskidx = 0;
	ft_memset(resul, 0, sizeof(void *) * lstsz);
	ft_memset(mask, 255, sizeof(int) * lstsz);
	while (list)
	{
		mask[maskidx] = 1;
		if (ft_findptrinarr(resul, list->content, i) == -1)
		{
			resul[i] = list->content;
			mask[maskidx] = 0;
			i++;
		}
		list = list->next;
		maskidx++;
	}
	free (resul);
	return (i);
}

int	ft_lstdeldup(t_list **list, void (*delnde)(void *))
{
	int	*mask;
	int	sz;

	mask = malloc (ft_lstsize((*list)) + 1);
	if (!mask)
		return (-1);
	sz = ft_lstdupmask((*list), mask, ft_lstsize((*list)) + 1);
	ft_lstcullpat(list, mask, NULL, delnde);
	free (mask);
	return (sz);
}
