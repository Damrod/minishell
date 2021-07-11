/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:29:03 by hellnhell         #+#    #+#             */
/*   Updated: 2021/07/07 20:30:51 by nazurmen         ###   ########.fr       */
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

void	free_and_nullify(void **tofree)
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

static void	config_bitmasks(unsigned short *bitmask, unsigned short *bitmask2,
			char checkdepth)
{
	*bitmask2 = 0;
	*bitmask = 0;
	if (checkdepth == CHECK_ONLY_LOW)
	{
		*bitmask2 = 0;
		*bitmask = 0xFF00U;
	}
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
	if (checkdepth == CHECK_ANYQUOTE)
	{
		*bitmask2 = 0;
		*bitmask = 0;
	}
}



char cmp_chars(unsigned short a, unsigned short b, char checkdepth)
{
	unsigned short	bitmask;
	unsigned short	bitmask2;
	unsigned short	bitmask3;
	unsigned short	bitmask4;
	char			aggregate;

	if (checkdepth == CHECK_ANYQUOTE)
	{
		config_bitmasks(&bitmask, &bitmask2, CHECK_DBLQUOTE);
		config_bitmasks(&bitmask3, &bitmask4, CHECK_SNGQUOTE);
		aggregate = ((a & ~bitmask) == (b | bitmask2));
		return (aggregate || ((a & ~bitmask3) == (b | bitmask4)));
	}
	config_bitmasks(&bitmask, &bitmask2, checkdepth);
	return ((a & ~bitmask) == (b | bitmask2));
}

int	ft_wstrncmp(unsigned short *s1, const char *str2, char checkdepth, size_t n)
{
	int					a;
	size_t				i;
	unsigned short		*s2;

	if (n == 0)
		return (0);
	s2 = upcast_str(str2);
	if (!s2)
		return (-0xFFFFF);
	i = 0;
	while (s1[i] && cmp_chars(s1[i], s2[i], checkdepth) && (i < n - 1))
		i++;
	a = (int)s1[i] - (int)s2[i];
	free (s2);
	return (a);
}

void	handle_eot(int sig)
{
	extern char		**environ;

	(void) sig;
	if (sig == SIGINT)
	{
		g_term.inputstring = readline("marishell% ");
		return ;
	}
	if (sig == SIGQUIT && g_term.lastpid > 0)
	{
		kill(g_term.lastpid, SIGQUIT);
		return ;
	}
	free_and_nullify ((void **)&environ);
	free_and_nullify((void **)&g_term.inputstring);
	ft_printf("\n");
	exit(0);
}

//esto a libft o common(?)
static int	ft_strcmp(char *s1, char *s2)
{
	while (*s2 == *s1 && *s1)
	{
		s2++;
		s1++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	check_builtins(t_term *g_term, char ***env)
{
	if (ft_strcmp(g_term->args[0], "export") == 0)
	{
		ft_export(env, g_term);
		return (1);
	}
	else if (ft_strcmp(g_term->args[0], "env") == 0)
	{
		ft_env(*env);
		return (1);
	}
	else if (ft_strcmp(g_term->args[0], "unset") == 0)
	{
		ft_unset(env, g_term);
		return (1);
	}
	else if (ft_strcmp(g_term->args[0], "exit") == 0)
	{
		ft_exit(g_term);
		return (1);
	}
	return (0);
}

void miniexec(t_term *g_term, char ***env)
{
	if(!(check_builtins(g_term, env)))
	{
		check_path(g_term);
	}
}

int	main(int argc, char **argv)
{
	unsigned short	**str;
	size_t			i;
	extern char		**environ;

	(void)argc;
	(void)argv;
	environ = ft_dblptr_cpy((const char **)environ, NULL, 0);
	read_path(environ, &g_term);
	str = NULL;
	signal(SIGINT, handle_eot);
	signal(SIGQUIT, handle_eot);
	while (1)
	{
		g_term.inputstring = readline("marishell% ");
		if (!g_term.inputstring)
			break ;
		if (ft_strlen(g_term.inputstring) > 0)
			add_history(g_term.inputstring);
		if (g_term.inputstring && g_term.inputstring[0] == STX)
		{
			free_and_nullify((void **)&g_term.inputstring);
			break ;
		}
		str = get_args(g_term.inputstring);
		free_and_nullify((void **)&g_term.inputstring);
		if (!str)
			continue ;
		if (!na_calloc(ft_dblptrlen((void **)str) + 1, sizeof(void *),
				(void **)&g_term.args))
		{
			free_and_nullify((void **)&g_term.inputstring);
			break ;
		}
		i = 0;
		while (str[i])
		{
			char *param = "|";
			g_term.args[i] = downcast_wstr(str[i], 1);
			if (ft_wstrncmp(str[i], param, CHECK_ONLY_LOW, 2) == 0)
				ft_printf("equals %s\n", param);
			free (str[i]);
			free_and_nullify ((void **)&g_term.inputstring);
			i++;
		}
		free(str);
		apply_dblptr(g_term.args, print_dblptr);
printf("\n\n\n\ntest:\n\n");
//		ft_env(environ);
printf("\n\n\n\n");
//		ft_export(&environ, &g_term);
printf("\n\n\n\n");
		miniexec(&g_term, &environ);
		if (1)
		{
			ft_dblptr_free((void **)g_term.args);
		}
	}
	free(environ);
	environ = NULL;
	ft_printf("\n");
	return (0);
}
