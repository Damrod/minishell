/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 09:16:15 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/12 18:29:03 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char_in_str(char c, char *charset)
{
	int		i;

	i = 0;
	while (charset[i] != '\0' && c != '\0')
	{
		if (c == charset[i])
			return (0);
		i++;
	}
	return (1);
}

static size_t	substrlen(const char *substr, char *charset)
{
	const char	*src;

	src = substr;
	while (is_char_in_str(*substr, charset) && *substr != '\0')
		substr++;
	return ((size_t)(substr - src));
}

static int	storesubstr(const char *st, char **dest, char *cs)
{
	int				i;
	int				occur;
	int				a;

	i = 0;
	occur = 0;
	while (st[i])
	{
		a = ((i == 0 || (!is_char_in_str(st[i - 1], cs)))
				&& is_char_in_str(st[i], cs));
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

static void	append(char **resul, char *cs)
{
	int				i;
	int				j;
	char			*substr;

	i = 0;
	while (resul[i])
	{
		substr = malloc(sizeof(*substr) * (substrlen(resul[i], cs) + 1));
		if (substr == NULL)
			return ;
		j = 0;
		while (is_char_in_str(resul[i][j], cs) && resul[i][j])
		{
			substr[j] = resul[i][j];
			j++;
		}
		substr[j] = '\0';
		resul[i] = &substr[0];
		i++;
	}
}

char	**ft_split_ultimate(char const *s, char *cs)
{
	int				res_size;
	char			**resul;

	if (!s)
		return (NULL);
	res_size = storesubstr(s, NULL, cs);
	resul = malloc(sizeof(char **) * (res_size + 1));
	if (resul == NULL)
		return (NULL);
	storesubstr(s, resul, cs);
	append(resul, cs);
	return (resul);
}
