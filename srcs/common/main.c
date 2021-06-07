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

#include <minishell.h>

char	*read_line(t_tab *t)
{
//	char	*line;

//	line = NULL;
	get_next_line(0, &t->line);
	// creo que este get_next_line debería tener un tamaño de buffer de 1
	// y debería retornar si pilla algo especial, por ejemplo Ctrl+\, Ctrl + C
	// o Ctrl+ D
	return (t->line);
}

void	initt(t_tab *t)
{
	t->line = NULL;
	t->path = NULL;
}

void	ft_alloc_env(t_tab *t, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
		i++;
	t->our_env = (char **)malloc(sizeof(char *) * (i + 1));
	t->our_env[i] = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
			j++; // Esto es lo mismo que esto: j = ft_strlen(env[i])
		t->our_env[i] = (char *)malloc(sizeof(char) * (j + 1));
		/* sizeof(char) es siempre == 1; y es sizeof(char), no sizeof(char *) */
		i++;
	}
}

void	ft_copy_env(t_tab *t, char **env)
{
	int	i;
	int	j;

	i = 0;
	ft_alloc_env(t, env);
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			t->our_env[i][j] = env[i][j];
			j++;
		}
		t->our_env[i][j] = '\0';
		i++;
	}
}

void	ft_order_list(t_tab *t, t_dlist *lst, int i)
{
	(void)lst;
	while (t->orders[i])
	{
		//procesado de to
		printf("%s\n", t->orders[i]);
		i++;
	}
}

void	ft_miniloop(t_tab *t, t_dlist *lst)
{
	int	i;

	while (1)
	{
		i = 0;
		ft_putstr_fd("marishell% ", 1);
		//pillar signals
		t->line = read_line(t);
		//care quotes
		t->orders = ft_split(t->line, ';'); // si no entiendo mal, la idea es:
		// un comando compuesto es una secuencia válida de comandos en una
		// línea, independiendemente de si están separados por | o ;. El | o
		// ; al final de un comando simple es lo que nos proporciona el tipo
		// de comando simple que estamos tratando. Nos da la clave sobre cómo
		// redireccionar input y output, y nos dice qué tiene que hacer la shell
		// mientras espera que el comando hijo sea ejecutado.
		// Desde mi punto de vista t_tab->orders debería ser cada uno de los
		// comandos simples, y cada uno de ellos debería ser un nodo de la lista
		free(t->line);
		ft_order_list(t, lst, i);
	}
}

int	main(int argc, char **argv, char **env)
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
