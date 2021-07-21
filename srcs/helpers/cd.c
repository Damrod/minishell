/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:04:47 by nazurmen          #+#    #+#             */
/*   Updated: 2021/07/21 16:37:09 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>


static int	cd_error(char *path)
{
	ft_putstr_fd("cd: no such file or directory: ", 1);
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	return (1);
}

int	ft_cd(char **args)
{
	char	*path;
	int		i;

	i = 1;
	path = args[0];
	if (path && args[1])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 1);
		return (1);
	}
	if (!path)
		chdir(ft_getenv("HOME"));
	else if (-1 == chdir(path))
		return (cd_error(path));
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
