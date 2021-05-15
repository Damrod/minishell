/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 11:10:12 by aollero-          #+#    #+#             */
/*   Updated: 2020/06/29 17:38:00 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	res_len(int n)
{
	int		len;

	len = 0;
	if (n < 0)
		len = 1;
	while (len < 12 && n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len + 1);
}

static char	*ft_itoa_grl(int nbr, char *resul, int *b)
{
	if (nbr < 0)
	{
		resul[*b] = '-';
		(*b)++;
		ft_itoa_grl(-nbr, resul, b);
		return (resul);
	}
	if (nbr > 10 - 1)
		ft_itoa_grl(nbr / 10, resul, b);
	resul[(*b)++] = '0' + (nbr % 10);
	resul[(*b)] = '\0';
	return (resul);
}

static char	*overflow_handler(char *resul, int *b)
{
	resul[(*b)++] = '-';
	ft_itoa_grl(214748364, resul, b);
	resul[(*b)] = '8';
	resul[++(*b)] = '\0';
	return (resul);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		b;

	b = 0;
	res = malloc(sizeof(*res) * ((res_len(n)) + 1));
	if (res == NULL)
		return (NULL);
	if (n == -2147483648)
		overflow_handler(res, &b);
	else
		ft_itoa_grl(n, res, &b);
	return (res);
}
