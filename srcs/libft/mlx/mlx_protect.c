/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_protect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 11:42:17 by aollero-          #+#    #+#             */
/*   Updated: 2020/10/05 11:46:33 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*my_mlx(void *ptr)
{
	if (!(ptr))
		my_exit("Mlx pointer returned NULL", 1);
	return (ptr);
}
