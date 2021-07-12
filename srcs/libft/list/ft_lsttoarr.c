/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:06:40 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 11:07:31 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	**ft_lsttoarr(t_list *list, int *size)
{
	int		i;
	void	**retr;

	if (!size || *size < 0)
	{
		i = ft_lstsize(list);
		if (size)
			*size = i;
	}
	else
		i = *size;
	retr = malloc(sizeof(*retr) * (i + 1));
	if (!(retr))
		return (NULL);
	ft_memset(retr, 0, (sizeof(*retr) * (i + 1)));
	while (i)
	{
		retr[i - 1] = list->content;
		list = list->next;
		i--;
	}
	return (retr);
}
