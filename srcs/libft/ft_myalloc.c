/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:10:36 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 13:23:56 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "advice.h"

void	alloc_splitter(void *param, void **param2, int is_alloc, int nbr)
{
	static t_list	*ptrlst = NULL;

	if (is_alloc == 0)
		adv_free(param, &ptrlst);
	if (is_alloc == 1)
		adv_alloc(param, &ptrlst);
	if (is_alloc == 2)
		adv2alloc(param2, nbr, &ptrlst);
	if (is_alloc == 3)
		adv_gptrlstclear(&ptrlst);
	if (is_alloc == 4)
		adv_mperror((char *)param, nbr, &ptrlst);
}

void	my_free(void *ptr)
{
	alloc_splitter(ptr, NULL, 0, 0);
	return ;
}

void	*my_alloc(void *param)
{
	alloc_splitter(param, NULL, 1, 0);
	return (param);
}

void	**my2alloc(void **param, int size)
{
	void	**last;

	if (size < 0)
	{
		last = param;
		while (*last)
			last++;
		size = last - param;
	}
	alloc_splitter(NULL, param, 2, size);
	return (param);
}

void	ptrlstclear(void)
{
	alloc_splitter(NULL, NULL, 3, 0);
	return ;
}
