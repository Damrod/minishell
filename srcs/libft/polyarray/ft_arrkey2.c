/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_key2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:20:38 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/29 16:59:43 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arrkey.h"

unsigned long	*ft_arrlu(unsigned long *arr, size_t size, unsigned long key)
{
	while (size)
	{
		if (*arr == key)
			break ;
		arr++;
		size--;
	}
	if (*arr == key)
		return (arr);
	else
		return (NULL);
}

t_byte	*ft_arruchar(t_byte *arr, size_t size, t_byte key)
{
	while (size)
	{
		if (*arr == key)
			break ;
		arr++;
		size--;
	}
	if (*arr == key)
		return (arr);
	else
		return (NULL);
}

float	*ft_arrfloat(float *arr, size_t size, float key)
{
	while (size)
	{
		if (*arr == key)
			break ;
		arr++;
		size--;
	}
	if (*arr == key)
		return (arr);
	else
		return (NULL);
}

double	*ft_arrdbl(double *arr, size_t size, double key)
{
	while (size)
	{
		if (*arr == key)
			break ;
		arr++;
		size--;
	}
	if (*arr == key)
		return (arr);
	else
		return (NULL);
}

long double	*ft_arrldbl(long double *arr, size_t size, long double key)
{
	while (size)
	{
		if (*arr == key)
			break ;
		arr++;
		size--;
	}
	if (*arr == key)
		return (arr);
	else
		return (NULL);
}
