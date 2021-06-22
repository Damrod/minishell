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
	.args = NULL,
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

#define CHECK_ONLY_LOW 0
#define CHECK_SNGQUOTE 1
#define CHECK_DBLQUOTE 2

static void	config_bitmasks(unsigned short *bitmask, unsigned short *bitmask2,
			char checkdepth)
{
	*bitmask2 = 0;
	*bitmask = 0xFF00U;
	if (checkdepth == CHECK_SNGQUOTE)
	{
		*bitmask2 = FLAG_SNGQUOT;
		*bitmask = (FLAG_CIGNORE | FLAG_ESCAPED | FLAG_NOTSPCE | FLAG_DBLQUOT);
	}
	if (checkdepth == CHECK_DBLQUOTE)
	{
		*bitmask2 = FLAG_DBLQUOT;
		*bitmask = (FLAG_CIGNORE | FLAG_ESCAPED | FLAG_NOTSPCE | FLAG_SNGQUOT);
	}
}

int	ft_wstrncmp(unsigned short *s1, const char *str2, char checkdepth, size_t n)
{
	int					a;
	size_t				i;
	unsigned short		*s2;
	unsigned short		bitmask;
	unsigned short		bitmask2;

	if (n == 0)
		return (0);
	config_bitmasks(&bitmask, &bitmask2, checkdepth);
	s2 = upcast_str(str2);
	if (!s2)
		return (-0xFFFFF);
	i = 0;
	while (s1[i] && ((s1[i] & ~bitmask) == (s2[i] | bitmask2)) && (i < n - 1))
		i++;
	a = (int)s1[i] - (int)s2[i];
	free (s2);
	return (a);
}

char **oldenviron;

void	handle_eot(int sig)
{
	extern char		**environ;

	(void) sig;
	specialfree ((void **)&environ);
	specialfree((void **)&g_term.inputstring);
	/* ft_printf("%s\n", getenv("TERM")); */
	ft_printf("\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	unsigned short	**str;
	size_t			i;
	extern char		**environ;

	(void)argc;
	(void)argv;
	environ = ft_dblptr_cpy((const char **)environ, NULL, 0);
	str = NULL;
	signal(SIGINT, handle_eot);
	signal(SIGQUIT, handle_eot);
	while (1)
	{
		g_term.inputstring = readline("marishell% ");
		if (g_term.inputstring && g_term.inputstring[0] == STX)
		{
			specialfree((void **)&g_term.inputstring);
			break ;
		}
		str = get_args(g_term.inputstring);
		specialfree((void **)&g_term.inputstring);
		if (!str)
			continue ;
		if (!na_calloc(ft_dblptrlen((void **)str) + 1, sizeof(void *),
				(void **)&g_term.args))
		{
			specialfree((void **)&g_term.inputstring);
			break ;
		}
		i = 0;
		while (str[i])
		{
			g_term.args[i] = downcast_wstr(str[i], 1);
			free (str[i]);
			specialfree ((void **)&g_term.inputstring);
			i++;
		}
		free(str);
		apply_dblptr(g_term.args, print_dblptr);
		if (1)
		{
			freedblptr((void **)g_term.args);
		}
	}
	free(environ);
	free(oldenviron);
	environ = NULL;
	ft_printf("\n");
	return (0);
}
