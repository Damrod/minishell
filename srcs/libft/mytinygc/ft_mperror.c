/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mperror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:22:37 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 15:06:57 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "advice.h"

void	my_exit(char *str, int errnbr)
{
	alloc_splitter(str, NULL, 4, errnbr);
	return ;
}
