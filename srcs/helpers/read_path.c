/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 18:04:38 by emartin-          #+#    #+#             */
/*   Updated: 2021/06/03 19:33:22 by nazurmen         ###   ########.fr       */
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
/* 		if (t->tokens[0] == NULL) */
/* 			break ; */
/* 		else */
/* 		{ */
/* 			//aux = ft_strjoin(t->path[i], t->tokens[0]); */
/* 			aux = ft_strjoin_sl(t->path[i], t->tokens[0]); */
/* 			tmp = aux; */
/* 			//printf("valor de aux=    %s\n", aux); */
/* 			//printf("valor de tokens=    %s\n", t->tokens[0]); */
/* 			j = execve(tmp, t->tokens, env); */
/* 			/\* if (j < 0) *\/ */
/* 				//printf("%s\n", strerror(errno)); */
/* 			(void) j; */
/* 			free(aux); */
/* 			i++; */
/* 		} */
/* 	} */
/* } */

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
