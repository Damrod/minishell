/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ultimate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 23:39:24 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/13 14:27:02 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	dblptrlen(const char **strs)
{
	const char	**last;

	last = strs;
	while (*last)
		last++;
	return ((size_t)(last - strs));
}

size_t	ft_strlen_ult(ssize_t *size, const char **str)
{
	size_t	i;
	size_t	resul;

	if (*size < 0)
		*size = (signed)dblptrlen(str);
	if (*size == 0 || *str == NULL)
		return (0);
	resul = 0;
	i = 0;
	while (i < (unsigned) *size)
	{
		resul += ft_strlen(*(str + i));
		i++;
	}
	return (resul);
}

static void	*malloc_mng(ssize_t *size, const char **strs, const char *sep)
{
	char	*resul;
	int		fnl_pad;
	size_t	totsz;

	if (!strs || !*strs)
		return (NULL);
	if (*size != 0)
		fnl_pad = ft_strlen(sep);
	else
		fnl_pad = 0;
	totsz = ft_strlen_ult(size, strs) + (*size - 1) * fnl_pad;
	resul = malloc(sizeof(char) * totsz + 1);
	if (!resul)
		return (NULL);
	ft_memset(resul, '\0', totsz + 1);
	return (resul);
}

char	*ft_strjoin_ult(ssize_t sz, const char **strs, const char *sep)
{
	char	*res;
	ssize_t	i;
	size_t	aux;

	if (!strs || !*strs)
		return (NULL);
	res = malloc_mng(&sz, strs, sep);
	if (!res)
		return (NULL);
	if (sz == 0)
	{
		*res = '\0';
		return (res);
	}
	aux = 0;
	i = 0;
	while (i < sz - 1)
	{
		aux = ft_strlcat(res, strs[i], ft_strlen(res) + ft_strlen(strs[i]) + 1);
		aux = ft_strlcat(res, sep, aux + ft_strlen(sep) + 1);
		i++;
	}
	ft_strlcat(res, strs[i], aux + ft_strlen(strs[i]) + 1);
	return (res);
}
