/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:59:20 by aollero-          #+#    #+#             */
/*   Updated: 2020/07/08 10:43:40 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sou;

	if (!dest && !src)
		return (NULL);
	dst = (unsigned char *)dest;
	sou = (unsigned char *)src;
	while (n > 0)
	{
		n--;
		dst[n] = sou[n];
	}
	return ((void *)dst);
}
