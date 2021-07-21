/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:06:40 by aollero-          #+#    #+#             */
/*   Updated: 2021/07/16 22:50:56 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	**ft_lsttoarr(t_list *list, int *size)
{
	int		i;
	void	**retr;
	int		len;

	if (!size || *size < 0)
	{
		i = ft_lstsize(list);
		if (size)
			*size = i;
	}
	else
		i = *size;
	len = i;
	retr = malloc(sizeof(*retr) * (i + 1));
	if (!(retr))
		return (NULL);
	ft_memset(retr, 0, (sizeof(*retr) * (i + 1)));
	i = 1;
	while (i <= len)
	{
		retr[i - 1] = list->content;
		list = list->next;
		i++;
	}
	return (retr);
}
