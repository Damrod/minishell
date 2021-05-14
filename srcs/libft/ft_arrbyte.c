/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrbyte.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:58:34 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/29 17:01:10 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arrkey.h"

void	*ft_arrbyte(t_array *a, void *ky)
{
	if (a->type == 0)
		return (ft_strchr(a->cset, *(t_byte *)ky));
	if (a->type == 1)
		return (ft_arrint(a->cset, a->m * a->n, *(int *)ky));
	if (a->type == 2)
		return (ft_arrfloat(a->cset, a->m * a->n, *(float *)ky));
	if (a->type == 4)
		return (((void **) a->cset)[ft_findptrinarr(a->cset, ky, a->m * a->n)]);
	if (a->type == 5 || a->type == 3)
		return (ft_arruchar(a->cset, a->m * a->n, *(t_byte *)ky));
	if (a->type == 6)
		return (ft_arruint(a->cset, a->m * a->n, *(unsigned *)ky));
	if (a->type == 7)
		return (ft_arrsh(a->cset, a->m * a->n, *(short *)ky));
	if (a->type == 8)
		return (ft_arrush(a->cset, a->m * a->n, *(unsigned short *)ky));
	if (a->type == 9)
		return (ft_arrli(a->cset, a->m * a->n, *(long *)ky));
	if (a->type == 10)
		return (ft_arrlu(a->cset, a->m * a->n, *(long unsigned *)ky));
	if (a->type == 11)
		return (ft_arrdbl(a->cset, a->m * a->n, *(double *)ky));
	if (a->type == 12)
		return (ft_arrldbl(a->cset, a->m * a->n, *(long double *)ky));
	return (NULL);
}
