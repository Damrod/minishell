/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algebra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 10:18:41 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/12 10:19:04 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

void	rotvect2(double *vector[2], double len, double angle)
{
	double	aux;

	aux = *vector[0];
	*vector[0] = len * (*vector[0] * cos(-angle) - *vector[1] * sin(-angle));
	*vector[1] = len * (aux * sin(-angle) + *vector[1] * cos(-angle));
}
