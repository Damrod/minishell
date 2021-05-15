/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:14:56 by aollero-          #+#    #+#             */
/*   Updated: 2020/07/08 10:51:52 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int					a;
	size_t				i;

	i = 0;
	a = 0;
	while ((s1[i] == s2[i]) && (s1[i] != '\0') && (i < n - 1))
		i++;
	a = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (n == 0)
		a = 0;
	return (a);
}
