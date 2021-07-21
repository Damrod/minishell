/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:04:47 by nazurmen          #+#    #+#             */
/*   Updated: 2021/07/18 17:21:57 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>
#include <error_mng.h>

int	ft_cd(char **args)
{
	char	*path;
	int		i;

	i = 1;
	path = args[0];
	if (path && args[1])
		return (error_cmd("cd", NULL, "too many arguments", 1));
	if (!path)
		chdir(ft_getenv("HOME"));
	else if (-1 == chdir(path))
		return (error_cmd("cd", path, NULL, 1));
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
