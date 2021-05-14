/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:19:53 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/11 15:59:13 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*my_malloc(size_t size)
{
	return (my_alloc(malloc(size)));
}

static size_t	typesizes2(enum e_types type)
{
	if (type == 5)
		return (sizeof(unsigned char));
	if (type == 6)
		return (sizeof(unsigned int));
	if (type == 7)
		return (sizeof(short int));
	if (type == 8)
		return (sizeof(short unsigned int));
	if (type == 9)
		return (sizeof(long int));
	if (type == 10)
		return (sizeof(long unsigned int));
	if (type == 11)
		return (sizeof(double));
	if (type == 12)
		return (sizeof(long double));
	else
		return (0);
}

static size_t	typesizes(enum e_types type)
{
	if (type == 0)
		return (sizeof(char));
	if (type == 1)
		return (sizeof(int));
	if (type == 2)
		return (sizeof(float));
	if (type == e_void)
		return (sizeof(char));
	if (type == 4)
		return (sizeof(void *));
	else
		return (typesizes2(type));
}

t_array	*alloc_matrix(size_t m, size_t n, enum e_types tpe, t_byte *str)
{
	t_array	*array;

	array = my_malloc(sizeof(*array));
	array->type = tpe;
	array->usz = typesizes(tpe);
	array->m = m;
	array->n = n;
	array->setsz = m * n;
	if (!str)
	{
		str = my_malloc(array->usz * ((m * n) + 1));
		ft_memset(str, '\0', array->usz * ((m * n) + 1));
	}
	array->cset = str;
	return (array);
}

void	ft_wrtptr(char *c, char *str)
{
	size_t	size;

	size = ft_strlen(str);
	while (size > 0)
	{
		*c = *str;
		c++;
		str++;
		size--;
	}
}
