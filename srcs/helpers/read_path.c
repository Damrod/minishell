/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 18:04:38 by emartin-          #+#    #+#             */
/*   Updated: 2021/07/16 17:02:46 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* void	check_path(t_tab *t, char **env) */
/* { */
/* 	int		i; */
/* 	int		j; */
/* 	char	*aux; */
/* 	char	*tmp; */

/* 	i = 0; */

/* 	//exit q hay q gestionar con errno */
/* 	while (t->path[i]) */
/* 	{ */
/* 		if (g_term->args[0] == NULL) */
/* 			break ; */
/* 		else */
/* 		{ */
/* 			//aux = ft_strjoin(t->path[i], g_term->args[0]); */
/* 			aux = ft_strjoin_sl(t->path[i], g_term->args[0]); */
/* 			tmp = aux; */
/* 			//printf("valor de aux=    %s\n", aux); */
/* 			//printf("valor de tokens=    %s\n", g_term->args[0]); */
/* 			j = execve(tmp, g_term->args, env); */
/* 			/\* if (j < 0) *\/ */
/* 				//printf("%s\n", strerror(errno)); */
/* 			(void) j; */
/* 			free(aux); */
/* 			i++; */
/* 		} */
/* 	} */
/* } */

/*
void	read_path(t_tab *t, char **env)
{
	int		i;
//	char *test;

	i = 0;
	while (env[i])
	{
		//t->our_env[i] = ft_strdup(env[i]);
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			t->path = ft_split(&env[i][5], ':');
		i++;
	}
	//free(t->path);
}
*/

char	*ft_cat_path(char *path, char *arg)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!na_calloc((ft_strlen(path) + ft_strlen(arg) + 2),
			sizeof (char*), (void **)&ret))
		return (NULL);
	while (*path)
		ret[i++] = *path++;
	ret[i++] = '/';
	while (*arg)
		ret[i++] = *arg++;
	ret[i++] = 0;
	return (ret);
}

char	*ft_cat_rel_path(char *path, char *arg)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!na_calloc((ft_strlen(path) + ft_strlen(arg)),
			sizeof(char*), (void **)&ret))
		return (NULL);
	while (*path)
		ret[i++] = *path++;
	arg += 1;
	while (*arg)
		ret[i++] = *arg++;
	ret[i++] = 0;
	return (ret);
}

int	check_relat(char *execpath, char *cwd, char **args, int *status)
{
	int dir;
	int i;

	dir = 0;
	i = 0;
	while ((*args)[i])
	{
		if((*args)[i] == '/')
			dir++;
		i++;
	}
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

int	check_path(char **args, char **path)
{
	int		i;
	int			*status;
	char		cwd[1024];
	char		*execpath;

	getcwd(cwd, 1024);
	i = 0;
	status = malloc(sizeof(int));
	*status = -1;
	while (path[i])
	{
		if (!check_relat(execpath, cwd, args, status) && *status >= 0)
			continue ;
		if (args[0][0] == '/')
		{
			*status = execve(args[0], args, g_term.environ);
			if (*status >= 0)
				continue ;
		}
		execpath = ft_cat_path(path[i], args[0]);
		*status = execve(execpath, args, g_term.environ);
		free(execpath);
		i++;
	}
	if (*status < 0 || !path[i])
		printf("%s: command not found\n", args[0]);
	i = *status;
	free(status);
	return (i);
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

/* int main(int argc, char **argv, char **environ) */
/* { */
/* 	t_tab	tab; */
/* 	char **strings; */

/* 	read_path(&tab, g_term.environ); */
/* 	strings = ft_split(ft_getenv("PATH"), ':'); */
/* 	while (*tab.path) */
/* 	{ */
/* 		ft_printf("\"%s\"\n", *strings); */
/* 		ft_printf("\"%s\"\n", *tab.path); */
/* 		tab.path++; */
/* 		strings++; */
/* 	} */
/* } */
