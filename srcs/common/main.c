/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:29:03 by aollero           #+#    #+#             */
/*   Updated: 2021/07/13 18:37:56 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell0.h>
#include <libft.h>
#include <error_mng.h>
#include <wstrcmp.h>
#include <get_redirs.h>
#include <env.h>

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

int exec_cmd(t_dlist *cmd, char **env);



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
