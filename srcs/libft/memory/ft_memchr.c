/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:03:25 by aollero-          #+#    #+#             */
/*   Updated: 2020/06/29 17:03:55 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sou;
	unsigned int	i;

	sou = (unsigned char *)s;
	i = 0;
	while (i < n && sou[i] != (unsigned char)c)
		i++;
	if (i == n)
		return (NULL);
	else
		return ((void *)&sou[i]);
}
