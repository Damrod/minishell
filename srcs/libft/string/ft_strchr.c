/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:11:28 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/05 17:03:26 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*sou;
	unsigned int	i;

	sou = (char *)s;
	i = 0;
	while (sou[i] && sou[i] != (char)c)
		i++;
	if (!sou[i] && c)
		return (NULL);
	else
		return ((char *) & sou[i]);
}
