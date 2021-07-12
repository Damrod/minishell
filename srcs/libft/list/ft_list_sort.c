/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:20:47 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/27 16:21:15 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_list_sort(t_list **src, int (*cmp)())
{
	t_list	*a;
	t_list	*b;

	a = NULL;
	b = NULL;
	if (!*src || !(*src)->next)
		return ;
	ft_lstsplit_half(*src, &a, &b);
	ft_list_sort(&a, cmp);
	ft_list_sort(&b, cmp);
	ft_sorted_lst_merge(&a, b, cmp);
	*src = a;
}
