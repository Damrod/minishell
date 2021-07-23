/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 18:04:38 by emartin-          #+#    #+#             */
/*   Updated: 2021/07/23 22:36:01 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <error_mng.h>
#include <read_path.h>

static int	is_dir(char **args)
{
	int	i;
	int	dir;

	dir = 0;
	i = 0;
	while ((*args)[i])
	{
		if ((*args)[i] == '/')
			dir++;
		i++;
	}
	return (dir);
}

int	check_relat(char *execpath, char *cwd, char **args, int *status)
{
	int	dir;

	dir = is_dir(args);
	if ((args[0][0] == '.' && args[0][1]
		&& args[0][1] == '.' && args[0][2] == '/'))
		ft_makerelat(args);
	if ((args[0][0] == '.' && args[0][1]
		&& args[0][1] == '/') || ft_isalpha(args[0][0]))
	{
		if (args[0][0] == '.')
			execpath = ft_cat_rel_path(cwd, args[0]);
		else if (ft_isalpha(args[0][0]) && dir)
			execpath = ft_cat_path(cwd, args[0]);
		else
			execpath = ft_strdup("");
		*status = execve(execpath, args, g_term.environ);
		free(execpath);
		return (1);
	}
	return (0);
}

int	check_path2(int status, char **path, int i)
{
	if (status < 0 || !path[i])
		error_custom(NULL, NULL, NULL, "command not found");
	i = status;
	return (i);
}

int	check_path(char **args, char **path)
{
	int			i;
	char		cwd[1024];
	char		*execpath;
	int			status;

	getcwd(cwd, 1024);
	i = 0;
	while (path[i])
	{
		if (!check_relat(execpath, cwd, args, &status) && status >= 0)
			continue ;
		if (args[0][0] == '/')
		{
			status = execve(args[0], args, g_term.environ);
			if (status >= 0)
				continue ;
		}
		execpath = ft_cat_path(path[i], args[0]);
		status = execve(execpath, args, g_term.environ);
		free(execpath);
		i++;
	}
	if (selfassignment(&status, 127, status < 0 || !path[i]))
		ft_dprintf(2, "%s: %s\n", args[0], "command not found");
	return (status);
}

char	**read_path(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (ft_split(&env[i][5], ':'));
		i++;
	}
	return (NULL);
}
