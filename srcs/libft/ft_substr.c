/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:27:13 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/05 20:39:30 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*resul;
	size_t			aux;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i + start] && i < len)
		i++;
	aux = i;
	if (start >= ft_strlen(s))
		aux = 0;
	resul = malloc(sizeof(*resul) * aux + 1);
	if (resul == NULL)
		return (NULL);
	i = 0;
	while (s[i + start] && i < len && start < ft_strlen(s))
	{
		resul[i] = s[i + start];
		i++;
	}
	resul[i] = '\0';
	return (resul);
}
