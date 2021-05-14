/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advicemalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:15:34 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/30 09:44:11 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "advice.h"

void	adv_free(void *ptr, t_list **ptrlist)
{
	t_list	**indirect;
	t_list	*deleted;
	int		flag;

	flag = 1;
	indirect = ptrlist;
	while (*indirect)
	{
		while (*indirect && (*indirect)->content == ptr)
		{
			deleted = *indirect;
			*indirect = (*indirect)->next;
			if (flag)
				ft_lstdelone(deleted, free, free);
			else
				ft_lstdelone(deleted, NULL, free);
			flag = 0;
		}
		if (*indirect)
			indirect = &((*indirect)->next);
	}
	return ;
}

void	adv_gptrlstclear(t_list **ptrlst)
{
	ft_lstdeldup(ptrlst, free);
	ft_lstclear(ptrlst, free, free);
}

void	adv_mperror(char *error, int errnbr, t_list **ptrlst)
{
	if (error)
	{
		write(2, "Error\n", 6);
		write(2, error, strlen(error));
		write(2, "\n", 1);
	}
	adv_gptrlstclear(ptrlst);
	if (errnbr != 0)
		exit(errnbr);
}

void	*adv_alloc(void *param, t_list **ptrlst)
{
	t_list			*aux;

	if (param)
	{
		if (!na_lstnew(param, & aux))
			adv_mperror(strerror(errno), errno, ptrlst);
		ft_lstadd_front(ptrlst, aux);
	}
	else
		adv_mperror(strerror(errno), errno, ptrlst);
	return (param);
}

void	**adv2alloc(void **param, int size, t_list **ptrlst)
{
	char			**ret;
	t_list			*aux;

	ret = (char **)param;
	if (ret)
	{
		while (size)
		{
			if (!na_lstnew(*ret, & aux))
				adv_mperror(strerror(errno), errno, ptrlst);
			ft_lstadd_front(ptrlst, aux);
			ret++;
			size--;
		}
		if (!na_lstnew(param, & aux))
			adv_mperror(strerror(errno), errno, ptrlst);
		ft_lstadd_front(ptrlst, aux);
	}
	else
	{
		adv_mperror(strerror(errno), errno, ptrlst);
		exit(errno);
	}
	return ((void **)param);
}
