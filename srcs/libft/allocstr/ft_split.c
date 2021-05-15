/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 09:16:15 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/05 21:12:57 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	substrlen(const char *substr, char c)
{
	const char			*src;

	src = substr;
	while (!(*substr == c) && *substr != '\0')
		substr++;
	return ((size_t)(substr - src));
}

static int	storesubstr(const char *st, char **dest, char c)
{
	int				i;
	int				occur;
	int				a;

	i = 0;
	occur = 0;
	while (st[i])
	{
		a = ((i == 0 || (st[i - 1] == c))
				&& !(st[i] == c));
		if (a)
			occur++;
		if (dest != NULL && a)
			*(dest++) = (char *) & st[i];
		i++;
	}
	if (dest != NULL)
		*dest = NULL;
	return (occur);
}

static void	append(char **resul, char c)
{
	int				i;
	int				j;
	char			*substr;

	i = 0;
	while (resul[i])
	{
		substr = malloc(sizeof(*substr) * (substrlen(resul[i], c) + 1));
		if (substr == NULL)
			return ;
		j = 0;
		while (!(resul[i][j] == c) && resul[i][j])
		{
			substr[j] = resul[i][j];
			j++;
		}
		substr[j] = '\0';
		resul[i] = &substr[0];
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	int				res_size;
	char			**resul;

	if (!s)
		return (NULL);
	res_size = storesubstr(s, NULL, c);
	resul = malloc(sizeof(char **) * (res_size + 1));
	if (resul == NULL)
		return (NULL);
	storesubstr(s, resul, c);
	append(resul, c);
	return (resul);
}
