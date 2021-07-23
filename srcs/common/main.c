/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:29:03 by aollero           #+#    #+#             */
/*   Updated: 2021/07/23 12:22:26 by nazurmen         ###   ########.fr       */
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
	.cmdtable = NULL,
	.lineno = 0,
	.lastret = 0,
	.lastpid = 0,
	.waiting = 0
};

void	print_dblptr(const char *input)
{
	printf("%s\n", input);
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
	char	*arg;

	arg = downcast_wstr(str, 1);
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

t_simplcmd	*getcmds(t_dlist *cmd)
{
	return ((t_simplcmd *)cmd->content);
}

int		exec_cmd(t_dlist *cmd, char **env);
int		is_builtin(char *arg);
int		check_builtins(char **args, char ***env);

static void	loop_commands(t_list *args)
{
	t_dlist			*simplecmds;
	t_dlist			*cmds;

	simplecmds = split_into_simple_cmds(args);
	g_term.cmdtable = build_cmd_table(&simplecmds);
	cmds = g_term.cmdtable;
	while (cmds)
	{
		g_term.lastret = exec_cmd(cmds, g_term.environ);
		cmds = cmds->next;
	}
	comp_dtor(&g_term.cmdtable, NULL, 0);
}

static void	prompt_loop(void)
{
	char			*inputstring;
	t_list			*args;

	while (1)
	{
		g_term.lastpid = 0;
		inputstring = readline("marishell% ");
		if (!inputstring)
		{
			ft_putstr_fd("exit", 1);
			break ;
		}
		if (ft_strlen(inputstring) > 0)
			add_history(inputstring);
		g_term.lineno++;
		args = get_args(inputstring);
		free_and_nullify((void **)&inputstring, NULL, NULL, 1);
		if (!args)
			continue ;
		loop_commands(args);
	}
}

int	main(int argc, char **argv)
{
	extern char		**environ;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	g_term.environ = ft_dblptr_cpy((const char **)environ, NULL, 1);
	if (ft_getenv("PPID") && !ft_strncmp(ft_getenv("PPID"), "minishell", 10))
		signal(SIGINT, handle_eot);
	else
		signal(SIGINT, handle_int);
	signal(SIGQUIT, handle_eot);
	prompt_loop();
	ft_dblptr_free((void **)g_term.environ);
	ft_printf("\n");
	return (0);
}
