/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:33:51 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/05 21:24:38 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*get_out(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;

	if (!s)
		ret = ((void *) 0);
	if (!(*f))
		ret = ft_strdup(s);
	return (ret);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*resul;

	if (!s || !(*f))
		return (get_out(s, (*f)));
	resul = malloc(sizeof(*s) * ft_strlen(s) + 1);
	if (resul == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		resul[i] = (*f)(i, s[i]);
		i++;
	}
	resul[i] = '\0';
	return (resul);
}
