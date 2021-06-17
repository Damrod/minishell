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
#include <libft.h>
#include <minishell0.h>
#include <minishell.h>

t_term	g_term = {
	.inputstring = NULL,
	.cmds = NULL
};

void	print_dblptr(const char *input)
{
	printf("%s\n", input);
}

void	apply_dblptr(char **data, void (*f)())
{
	size_t	len;

	len = 0;
	if (data)
	{
		while (data[len])
		{
			f(data[len]);
			len++;
		}
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

void	specialfree(void **tofree)
{
	free(*tofree);
	*tofree = NULL;
}

char	*downcast_wstr(const unsigned short *str, char is_low)
{
	char	*result;
	size_t	i;

	if (!na_calloc(sizeof(*result), ft_wstrlen(str, UNTIL_END_OF_STRING) + 1,
			(void **)&result))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (is_low)
			result[i] = (char)str[i];
		else
			result[i] = (char)(str[i] >> 8);
		i++;
	}
	return (result);
}

void	handle_eot(int sig)
{
	(void) sig;
	specialfree((void **)&g_term.inputstring);
	ft_printf("\n");
	exit(0);
}

/* int	main(int argc, char **argv, char **environ) */
/* { */
/* 	unsigned short	**str; */
/* 	unsigned short	**origstr; */

/* 	(void)argc; */
/* 	(void)argv; */
/* 	(void)environ; */
/* 	str = NULL; */
/* 	signal(SIGINT, handle_eot); */
/* 	signal(SIGQUIT, handle_eot); */
/* 	while (1) */
/* 	{ */
/* 		g_term.inputstring = readline("marishell% "); */
/* 		if (g_term.inputstring && g_term.inputstring[0] == STX) */
/* 		{ */
/* 			specialfree((void **)&g_term.inputstring); */
/* 			break ; */
/* 		} */
/* 		str = get_args(g_term.inputstring); */
/* 		specialfree((void **)&g_term.inputstring); */
/* 		if (!str) */
/* 			continue ; */
/* 		origstr = str; */
/* 		while (*str) */
/* 		{ */
/* 			g_term.inputstring = downcast_wstr(*str, 1); */
/* 			ft_printf("---%s---\n", g_term.inputstring); */
/* 			free (*str); */
/* 			specialfree ((void **)&g_term.inputstring); */
/* 			str++; */
/* 		} */
/* 		free(origstr); */
/* 	} */
/* 	ft_printf("\n"); */
/* 	return (0); */
/* } */

int	main(int argc, char **argv, char const **environ)
{
	char	**str;
	str = ft_dblptr_cpy(environ, "hitokisi\n", 0);
	(void)argc;
	(void)argv;
	apply_dblptr(str, print_dblptr);
	free(str);
	/* freedblptr((void **)str); */
}
