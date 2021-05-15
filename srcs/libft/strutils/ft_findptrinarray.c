/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findptrinarray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:21:06 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 11:21:38 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_findptrinarr(void **array, void *key, int size)
{
	int	i;

	i = 0;
	while (size)
	{
		if (*array == key)
			break ;
		array++;
		i++;
		size--;
	}
	if (*array != key)
		return (-1);
	else
		return (i);
}
