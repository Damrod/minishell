/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 18:04:38 by emartin-          #+#    #+#             */
/*   Updated: 2021/06/25 20:58:52 by nazurmen         ###   ########.fr       */
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
	arg += 2;
	while (*arg)
		ret[i++] = *arg++;
	ret[i++] = 0;
	return (ret);
}

int	check_relat(char *execpath, char *cwd, t_term *g_term, int *status)
{
	if ((g_term->args[0][0] == '.' && g_term->args[0][1]
		&& g_term->args[0][1] == '/') || ft_isalpha(g_term->args[0][0]))
	{
		if (g_term->args[0][0] == '.')
			execpath = ft_cat_rel_path(cwd, g_term->args[0]);
		else if (ft_isalpha(g_term->args[0][0]))
			execpath = ft_cat_path(cwd, g_term->args[0]);
		*status = execve(execpath, g_term->args, g_term->environ);
		free(execpath);
		return (1);
	}
	return (0);
}

void	check_path(t_term *g_term)
{
	size_t	i;
	int		*status;
	char	cwd[1024];
	char	*execpath;

	getcwd(cwd, 1024);
	i = 0;
	status = malloc(sizeof(int));
	*status = -1;
	while (g_term->path[i])
	{
		if (!check_relat(execpath, cwd, g_term, status) && *status >= 0)
			continue ;
		if (g_term->args[0][0] == '/')
		{
			*status = execve(g_term->args[0], g_term->args, g_term->environ);
			if (*status >= 0)
				continue ;
		}
		execpath = ft_cat_path(g_term->path[i], g_term->args[0]);
		*status = execve(execpath, g_term->args, g_term->environ);
		free(execpath);
		i++;
	}
	if (*status < 0 || !g_term->path[i])
		printf("command not found: %s\n", g_term->args[0]);
	free(status);
}

void	read_path(char **env, t_term *g_term)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			g_term->path = ft_split(&env[i][5], ':');
		i++;
	}
}

/* int main(int argc, char **argv, char **environ) */
/* { */
/* 	t_tab	tab; */
/* 	char **strings; */

/* 	read_path(&tab, environ); */
/* 	strings = ft_split(getenv("PATH"), ':'); */
/* 	while (*tab.path) */
/* 	{ */
/* 		ft_printf("\"%s\"\n", *strings); */
/* 		ft_printf("\"%s\"\n", *tab.path); */
/* 		tab.path++; */
/* 		strings++; */
/* 	} */
/* } */
