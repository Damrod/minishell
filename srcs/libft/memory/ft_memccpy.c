/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:01:28 by aollero-          #+#    #+#             */
/*   Updated: 2020/07/01 09:24:41 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sou;
	unsigned int	i;

	dst = (unsigned char *)dest;
	sou = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst[i] = sou[i];
		if (sou[i] == (unsigned char)c)
			break ;
		i++;
	}
	if (i == n)
		return (NULL);
	else
	{
		i++;
		return ((void *)&dst[i]);
	}
}
