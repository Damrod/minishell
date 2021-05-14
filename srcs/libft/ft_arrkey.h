/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrkey.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:24:58 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/05 11:52:51 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARRKEY_H
# define FT_ARRKEY_H

# include "libft.h"

int				*ft_arrint(int *arr, size_t size, int key);
unsigned int	*ft_arruint(unsigned int *arr, size_t size, unsigned int key);
unsigned short	*ft_arrush(unsigned short *arr, size_t size,
					unsigned short key);
short			*ft_arrsh(short *arr, size_t size, short key);
long			*ft_arrli(long *arr, size_t size, long key);
unsigned long	*ft_arrlu(unsigned long *arr, size_t size,
					unsigned long key);
t_byte			*ft_arruchar(t_byte *arr, size_t size, t_byte key);
float			*ft_arrfloat(float *arr, size_t size, float key);
double			*ft_arrdbl(double *arr, size_t size, double key);
long double		*ft_arrldbl(long double *arr, size_t size, long double key);

#endif
