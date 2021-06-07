/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_our_implement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 18:47:06 by nazurmen          #+#    #+#             */
/*   Updated: 2020/10/13 20:06:48 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_our_implement(t_tab *t)
{
	if (!t->tokens[0])
		return (1);
	if (ft_strncmp(t->tokens[0], "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(t->tokens[0], "cd", 3) == 0)
		return (ft_cd(&t->tokens[1]));
	if (ft_strncmp(t->tokens[0], "echo", 5) == 0)
		return (ft_echo(&t->tokens[1]));
	else
		return (1);
}
