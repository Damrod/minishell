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

#include <libft.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*resul;
	size_t	origlen;
	size_t	reslen;
	size_t	diff;

	if (!s)
		return (NULL);
	origlen = ft_strlen(s);
	reslen = origlen;
	if (reslen > len)
		reslen = len;
	if (origlen < start)
		diff = 0;
	else
		diff = origlen - start;
	if (reslen > diff)
		reslen = diff;
	resul = ft_calloc(reslen + 1, sizeof(*resul));
	if (resul == NULL)
		return (NULL);
	ft_memcpy(resul, s + start, reslen);
	return (resul);
}
