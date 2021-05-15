/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:26:04 by aollero-          #+#    #+#             */
/*   Updated: 2020/06/29 17:26:21 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s)
{
	char	*des;
	int		i;

	des = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (des == NULL)
		return (NULL);
	i = 0;
	while (*(s + i) != '\0')
	{
		*(des + i) = *(s + i);
		i++;
	}
	*(des + i) = '\0';
	return (des);
}
