/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelmany.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 10:45:31 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 10:46:39 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LSTDELMANY_H
# define FT_LSTDELMANY_H

typedef struct s_funct
{
	void		(*delcont)(void *arg);
	void		(*delnode)(void *arg);
}				t_delfunct;

#endif
