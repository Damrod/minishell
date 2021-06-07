/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:29:03 by hellnhell         #+#    #+#             */
/*   Updated: 2021/06/06 19:21:18 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_line(t_tab *t)
{
//	char	*line;

//	line = NULL;
	get_next_line(0, &t->line);
	return(t->line);
}

void	initt(t_tab *t)
{
	t->line = NULL;
	t->path = NULL;
}

void ft_alloc_env(t_tab *t, char **env)
{
	int i;
	int j;

	i = 0;
	while(env[i])
		i++;
	t->our_env = (char **)malloc(sizeof(char *) * (i + 1));
	t->our_env[i] = NULL;
	i = 0;
	while(env[i])
	{
		j = 0;
		while(env[i][j])
			j++;
		t->our_env[i] = (char *)malloc(sizeof(char *) * (j + 1));
		i++;
	}
}

void ft_copy_env(t_tab *t, char **env)
{
	int i;
	int j;

	i = 0;
	ft_alloc_env(t, env);
	while(env[i])
	{
		j = 0;
		while(env[i][j])
		{
			t->our_env[i][j] = env[i][j];
			j++;
		}
		t->our_env[i][j] = '\0';
		i++;
	}
}



///

void ft_order_list(t_tab *t, t_dlist *lst, int i)
{
	(void)lst;
	while(t->orders[i])
	{
		//procesado de to
printf("%s\n", t->orders[i]);
		i++;
	}
}

void ft_miniloop(t_tab *t, t_dlist *lst)
{
	int i;

	while(1)
	{
		i = 0;
		ft_putstr_fd("marishell% ", 1);
		//pillar signals
		t->line = read_line(t);
		//care quotes
		t->orders = ft_split(t->line, ';');
		free(t->line);
		ft_order_list(t, lst, i);
	}
}

int		main(int argc, char **argv, char **env)
{
	t_tab	*t;
	t_dlist	*lst;
//	int		i;

	(void)argc;
	(void)argv;
	lst = NULL;
	t = malloc (sizeof(t_tab));
	initt(t);

	ft_copy_env(t, env);
	ft_miniloop(t, lst);

/*	caca anterior
	while (1)
	{
		i = 0;
		ft_putstr_fd("marishell% ", 1);
		t->line = read_line(t);
		t->orders = ft_split(t->line, ';');
		while (t->orders[i])
		{
			t->tokens = ft_split_com(t->orders[i], ' ',t);
			if(check_our_implement(t))
			{
			//	read_path(t, env);
			//	check_path(t, env);
			}
			i++;
			free(t->tokens);
		}
		free(t->orders);
	}
*/

}
