/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:30:21 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/05 21:05:09 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_out(char const *s1, char const *s2)
{
	char	*ret;

	if (!s1 && !s2)
		ret = ((void *) 0);
	else
	{
		if (!s1)
			ret = ft_strdup(s2);
		else
			ret = ft_strdup(s1);
	}
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*resul;
	size_t	i;

	if (!s1 || !s2)
		return (get_out(s1, s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	resul = ft_calloc(sizeof(*resul), (len1 + len2) + 1);
	if (!resul)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		resul[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		resul[i] = s2[i - len1];
		i++;
	}
	return (resul);
}
