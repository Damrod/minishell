/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:04:47 by nazurmen          #+#    #+#             */
/*   Updated: 2021/07/13 17:26:35 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_cd(char **args)
{
	char	*path;
	int		i;

	i = 1;
	path = args[0];
	if (!path)
		chdir(getenv("HOME"));
	else if (-1 == chdir(path))
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else
	{
		while (args[i])
		{
			path = ft_strjoin(path, args[i]);
			if (args[++i])
				path = ft_strjoin(path, " ");
		}
	}
	return (0);
}
