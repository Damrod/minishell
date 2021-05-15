/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 16:02:55 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/11 16:05:35 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*elem(t_array *array, size_t i, size_t j)
{
	return ((t_byte *)array->cset + (i * array->n + j) * array->usz);
}