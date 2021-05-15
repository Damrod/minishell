/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:24:00 by aollero-          #+#    #+#             */
/*   Updated: 2020/07/08 14:55:18 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ret;
	size_t			req;

	req = nmemb * size;
	if (!(na_malloc(req, (void **) & ret)))
		return (NULL);
	ft_memset(ret, 0, req);
	return ((void *)ret);
}
