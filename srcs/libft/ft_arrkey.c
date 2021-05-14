/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:19:05 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/29 16:26:41 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arrkey.h"

int	*ft_arrint(int *arr, size_t size, int key)
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

unsigned int	*ft_arruint(unsigned int *arr, size_t size, unsigned int key)
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

unsigned short	*ft_arrush(unsigned short *arr, size_t size, unsigned short key)
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

short	*ft_arrsh(short *arr, size_t size, short key)
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

long	*ft_arrli(long *arr, size_t size, long key)
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
