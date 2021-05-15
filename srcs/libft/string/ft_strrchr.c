/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:12:11 by aollero-          #+#    #+#             */
/*   Updated: 2020/07/06 15:21:04 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*sou;
	unsigned int	i;
	size_t			pos;
	char			bool;

	sou = (unsigned char *)s;
	i = 0;
	bool = 1;
	while (sou[i])
	{
		if (sou[i] == (unsigned char)c)
		{
			bool = 0;
			pos = i;
		}
		i++;
	}
	if (bool && c != '\0')
		return (NULL);
	else if (c == '\0')
		return ((char *)&sou[ft_strlen((char *)sou)]);
	else
		return ((char *)&sou[pos]);
}
