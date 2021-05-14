/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advice.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:35:37 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 13:47:36 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADVICE_H
# define ADVICE_H
# include "libft.h"

int			ft_lstdeldup(t_list **list, void (*delnde)(void *));
void		adv_free(void *ptr, t_list **ptrlist);
void		adv_gptrlstclear(t_list **ptrlst);
void		adv_mperror(char *error, int errnbr, t_list **ptrlst);
void		*adv_alloc(void *param, t_list **ptrlst);
void		**adv2alloc(void **param, int size, t_list **ptrlst);
void		alloc_splitter(void *param, void **param2, int is_alloc, int nbr);

#endif
