/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:06:40 by aollero-          #+#    #+#             */
/*   Updated: 2021/07/16 19:35:02 by nazurmen         ###   ########.fr       */
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
	{
printf("pillasizedeparam\n");
		i = *size;
	}
	retr = malloc(sizeof(*retr) * (i + 1));
	if (!(retr))
		return (NULL);
	ft_memset(retr, 0, (sizeof(*retr) * (i + 1)));
	while (i)
	{
printf("precrash3\n");
printf("%icontent: %s\n", (*size) - i, (char *)list->content);
		retr[i - 1] = list->content;
		list = list->next;
		i--;
printf("postcrash3\n");
	}
	return (retr);
}
