/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:16:29 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 18:05:00 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int					resul;
	int					sign;

	sign = 1;
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	resul = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		resul = 10 * resul + (*nptr - '0');
		nptr++;
	}
	return (sign * resul);
}

int64_t	ft_atol(const char *nptr)
{
	int64_t			resul;
	int64_t			sign;

	sign = 1;
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	resul = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		resul = 10 * resul + (*nptr - '0');
		nptr++;
	}
	return (sign * resul);
}

int	ft_atoi_adv(char **nptr)
{
	int					sign;
	int					resul;

	sign = 1;
	while (**nptr == '\t' || **nptr == '\n' || **nptr == '\v'
		|| **nptr == '\f' || **nptr == '\r' || **nptr == ' ')
		(*nptr)++;
	if (**nptr == '-')
	{
		sign = -1;
		(*nptr)++;
	}
	else if (**nptr == '+')
		(*nptr)++;
	resul = 0;
	while (**nptr >= '0' && **nptr <= '9')
	{
		resul = 10 * resul + (**nptr - '0');
		(*nptr)++;
	}
	return (sign * resul);
}

int64_t	ft_atol_adv(char **nptr)
{
	int64_t			sign;
	int64_t			resul;

	sign = 1;
	while (**nptr == '\t' || **nptr == '\n' || **nptr == '\v'
		   || **nptr == '\f' || **nptr == '\r' || **nptr == ' ')
		(*nptr)++;
	if (**nptr == '-')
	{
		sign = -1;
		(*nptr)++;
	}
	else if (**nptr == '+')
		(*nptr)++;
	resul = 0;
	while (**nptr >= '0' && **nptr <= '9')
	{
		resul = 10 * resul + (**nptr - '0');
		(*nptr)++;
	}
	return (sign * resul);
}
