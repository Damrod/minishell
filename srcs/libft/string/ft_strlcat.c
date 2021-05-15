/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:08:39 by aollero-          #+#    #+#             */
/*   Updated: 2020/07/07 17:37:04 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char				*dest;
	const char			*s;
	size_t				n;
	size_t				dstlen;

	s = src;
	n = size;
	dest = dst;
	while (n-- && *dst)
		dst++;
	dstlen = dst - dest;
	n = size - dstlen;
	if (!n)
		return (dstlen + ft_strlen(src));
	while (*src)
	{
		if (n != 1)
		{
			*(dst++) = *src;
			n--;
		}
		src++;
	}
	*dst = '\0';
	return (dstlen + (src - s));
}
