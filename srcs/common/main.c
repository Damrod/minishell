/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:29:03 by aollero           #+#    #+#             */
/*   Updated: 2021/06/06 19:21:18 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell0.h>
#include <libft.h>
#include <error_mng.h>
#include <wstrcmp.h>
#include <get_redirs.h>

t_dlist	*build_cmd_table(t_dlist **simplecmds);
void	*comp_dtor(t_dlist **compcmd, t_dlist **simplecmds, bool isprintsynerr);

t_term	g_term = {
	.environ = NULL,
	.args = NULL,
	.cmdtable = NULL,
	.simplecmds = NULL,
	.inputstring = NULL,
	.lineno = 0,
	.lastret = 0,
	.lastpid = 0
};

void	print_dblptr(const char *input)
{
	printf("%s\n", input);
}

void	ft_dblptr_foreach(char **data, void (*f)())
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

int	get_pipes(void *src, void *key)
{
	unsigned short	*a;
	char			*b;

	a = src;
	b = key;
	return (ft_wstrncmp(a, b, CHECK_NOTQUOTE, 2));
}

t_dlist	*split_into_simple_cmds(t_list *compcmd)
{
	return (ft_lstsplit(compcmd, "|", get_pipes));
}

void	display(void *str, int i)
{
	char *arg;

	arg = downcast_wstr(str, 1);
	/* ft_printf("%d, %s\n", i, str); */
	ft_printf("%d, %s\n", i, arg);
	free (arg);
}

void	ft_dblptr_display(char **dblptr, void (*p)())
{
	size_t	i;

	i = 0;
	while (dblptr[i])
	{
		p(dblptr[i], i);
		i++;
	}
}

t_simplcmd *getcmds(t_dlist *cmd)
{
	return ((t_simplcmd *)cmd->content);
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

int exec_cmd(t_dlist *cmd, char **env);

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
	extern char		**environ;
	t_dlist			*cmds;

	(void)argc;
	(void)argv;
	environ = ft_dblptr_cpy((const char **)environ, NULL, 0);
	read_path(environ, &g_term);
	signal(SIGINT, handle_eot);
	signal(SIGQUIT, handle_eot);
	while (1)
	{
		g_term.inputstring = readline("marishell% ");
		if (!g_term.inputstring)
			break ;
		if (ft_strlen(g_term.inputstring) > 0)
			add_history(g_term.inputstring);
		g_term.lineno++;
		g_term.args = get_args(g_term.inputstring);
		free_and_nullify((void **)&g_term.inputstring, NULL, NULL, 1);
		if (!g_term.args)
			continue ;
printf("\n\n\n\ntest:\n\n");
//		ft_env(environ);
printf("\n\n\n\n");
//		ft_export(&environ, &g_term);
printf("\n\n\n\n");
		miniexec(&g_term, &environ);
		g_term.simplecmds = split_into_simple_cmds(g_term.args);
		g_term.cmdtable = build_cmd_table(&g_term.simplecmds);
		cmds = g_term.cmdtable;
		while (cmds)
		{
			g_term.lastret = exec_cmd(cmds, environ);
			cmds = cmds->next;
		}
		comp_dtor(&g_term.cmdtable, NULL, 0);
	}
	free(environ);
	environ = NULL;
	ft_printf("\n");
	return (0);
}
