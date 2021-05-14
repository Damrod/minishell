/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:04:57 by aollero-          #+#    #+#             */
/*   Updated: 2020/07/06 14:04:59 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sou;
	unsigned int	i;

	if (n == 0)
		return (0);
	dst = (unsigned char *)s2;
	sou = (unsigned char *)s1;
	i = 0;
	while (i < n - 1 && dst[i] == sou[i])
		i++;
	return ((int)(sou[i] - dst[i]));
}
