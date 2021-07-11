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
	.lastret = 0
};


/* int handle_redir_push(t_dlist **cmds, unsigned short *arg) */
/* { */
/* 	unsigned char	type; */
/* 	t_compcmd		*cmd; */

/* 	type = get_type(arg); */
/* 	if (is_redir(arg)) */
/* 		cmd = makecmpcmd(NULL); */
/* 	else if (is_pipe(arg)) */
/* 		return (EXIT_FAILURE); */
/* 	else */
/* 		cmd = makecmpcmd(arg); */
/* 	ft_dlstpush_front(cmds, cmd); */
/* 	cmpcmd(cmds)->type = type; */
/* } */

/* int	error_syntax(unsigned short *arg); */

/* int	fill_cmd_table(t_dlist **cmds, unsigned short *arg) */
/* { */
/* 	char	**aux; */

/* 	if (!*cmds) */
/* 	{ */
/* 		if (!is_pipe(arg)) */
/* 		{ */
/* 			ft_dlstpush_front(cmds, makecmpcmd(arg)); */
/* 			return (EXIT_SUCCESS); */
/* 		} */
/* 		else */
/* 			return (error_syntax(arg)); */
/* 	} */
/* 	else */
/* 	{ */
/* 		if (cmpcmd(cmds)->type == TYPE_PIPE) */
/* 		{ */
/* 		} */
/* 	} */
/* 		|| cmpcmd(cmds)->type == TYPE_PIPE */
/* 		if (!*cmds) */
/* 		{ */
/* 			ft_dlstpush_front(cmds, makecmpcmd(arg)); */
/* 			return (EXIT_SUCCESS); */
/* 		} */
/* 		if (is_redir(arg) && cmpcmd(cmds)->type > TYPE_HEREDOC) */
/* 			handle_redir_push(cmds, arg); */
/* 		else if (is_redir(arg) */
/* 				 || (ft_wstrncmp(arg, "|", CHECK_NOTQUOTE, 2) == 0 */
/* 					&& cmpcmd(cmds)->type == TYPE_PIPE)) */
/* 			return (error_syntax(arg)); */
/* 		else */
/* 			ft_dlstpush_front(cmds, makecmpcmd(arg)); */
/* 		return (EXIT_SUCCESS); */
/* 	} */
/* 	if (ft_wstrncmp(arg, "|", CHECK_NOTQUOTE, 2) == 0) */
/* 		cmpcmd(cmds)->type = TYPE_PIPE; */
/* 	else if (!*cmds || cmpcmd(cmds)->type == TYPE_PIPE) */
/* 	{ */
/* 		ft_dlstpush_front(cmds, makecmpcmd(arg)); */
/* 		return (EXIT_SUCCESS); */
/* 	} */
/* 	return (EXIT_SUCCESS); */
/* } */


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

/* t_compcmd	*cmpcmd(t_dlist **cmd) */
/* { */
/* 	if (*cmd) */
/* 		return ((t_compcmd *)((*cmd)->content)); */
/* 	return (NULL); */
/* } */

/* int add_arg(t_compcmd *cmpcmd, char *arg) */
/* { */
/* 	char **aux; */

/* 	aux = cmpcmd->args; */
/* 	cmpcmd->args = ft_dblptr_cpy((const char **)cmpcmd->args, arg, 0); */
/* 	if (!cmpcmd->args) */
/* 		return (EXIT_FAILURE); */
/* 	free (aux); */
/* 	cmpcmd->type = TYPE_END; */
/* 	return (EXIT_SUCCESS); */
/* } */

/* t_compcmd	*makecmpcmd(unsigned short *arg) */
/* { */
/* 	t_compcmd	*cmd; */
/* 	char		**res; */
/* 	size_t		size; */

/* 	size = 0; */
/* 	if(arg) */
/* 		size = 1; */
/* 	if (!na_calloc(1, sizeof(*cmd), (void **)&cmd)) */
/* 		return (NULL); */
/* 	if (!na_calloc(size + 1, sizeof(*res), (void **)&res)) */
/* 		return (NULL); */
/* 	res[0] = downcast_wstr(arg, 1); */
/* 	cmd->args = res; */
/* 	cmd->type = TYPE_END; */
/* 	return(cmd); */
/* } */

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
	/* t_list			*str; */
	/* t_dlist			*cmds; */
	extern char		**environ;

	(void)argc;
	(void)argv;
	environ = ft_dblptr_cpy((const char **)environ, NULL, 0);
	g_term.args = NULL;
	signal(SIGINT, handle_eot);
	signal(SIGQUIT, handle_eot);
	while (1)
	{
		g_term.inputstring = readline("marishell% ");
		g_term.lineno++;
		if (g_term.inputstring && g_term.inputstring[0] == STX)
		{
			free_and_nullify((void **)&g_term.inputstring, NULL, NULL, 1);
			break ;
		}
		g_term.args = get_args(g_term.inputstring);
		free_and_nullify((void **)&g_term.inputstring, NULL, NULL, 1);
		if (!g_term.args)
			continue ;

		// SPLIT into simple commands START
		g_term.simplecmds = split_into_simple_cmds(g_term.args);
		// while (g_term.simplecmds && g_term.simplecmds->content)
		// {
			// ft_lstdisplay(g_term.simplecmds->content, display);
			// ft_lstclear((t_list **)&g_term.simplecmds->content, free, free);
			/* if (!g_term.simplecmds->next) */
			/* { */
			/* 	ft_dlstrewind(&g_term.simplecmds); */
			/* 	break ; */
			/* } */
			// g_term.simplecmds = g_term.simplecmds->next;
		// }
		/* printf("\nantepenul: %s\n", downcast_wstr(((t_list *)(g_term.simplecmds->content))->content, 1)); */
		// ft_dlstrewind(&g_term.simplecmds);
		// ft_lstclear((t_list **)&g_term.simplecmds, NULL, free);
		// SPLIT into simple commands END

		g_term.cmdtable = build_cmd_table(&g_term.simplecmds);
		/* t_dlist *cmdtable = g_term.cmdtable; */
		/* while (cmdtable) */
		/* { */
		/* 	ft_dblptr_display(getcmds(cmdtable)->args, print_dblptr); */
		/* 	ft_printf("type: %d, out: %d, in: %d\n", getcmds(cmdtable)->type, getcmds(cmdtable)->outfd, getcmds(cmdtable)->infd); */
		/* 	cmdtable = cmdtable->next; */
		/* } */
		t_dlist *cmds;

		cmds = g_term.cmdtable;
		while (cmds)
		{
			g_term.lastret = exec_cmd(cmds, environ);
			cmds = cmds->next;
		}
		comp_dtor(&g_term.cmdtable, NULL, 0);

		/* int infd; */
		/* int outfd; */

		/* g_term.lastret = get_redirs(&g_term.args, &infd, &outfd); */
		/* if (infd > STDERR_FILENO) */
		/* { */
		/* 	char *line; */

		/* 	while (get_next_line(infd, &line) > 0) */
		/* 	{ */
		/* 		ft_printf("%s\n", line); */
		/* 		free (line); */
		/* 	} */
		/* 	ft_printf("%s\n", line); */
		/* 	free_and_nullify((void **)&line, NULL, NULL, 1); */
		/* } */
		/* if (infd > STDERR_FILENO) */
		/* 	close(infd); */
		/* if (outfd > STDERR_FILENO) */
		/* 	close(outfd); */
		/* if (g_term.lastret) */
		/* { */
		/* 	ft_lstclear(&g_term.args, free, free); */
		/* 	continue ; */
		/* } */

		/* char *tmp2; */
		/* str = g_term.args; */
		/* while (str) */
		/* { */
		/* 	tmp2 = downcast_wstr(str->content, 1); */
		/* 	printf("%s\n", tmp2); */
		/* 	free(tmp2); */
		/* 	str = str->next; */
		/* } */
		/* ft_lstclear(&g_term.args, free, free); */

		/* ft_dblptr_foreach(g_term.args, print_dblptr); */
		/* if (1) */
		/* { */
		/* 	ft_dblptr_free((void **)g_term.args); */
		/* } */
	}
	free(environ);
	environ = NULL;
	ft_printf("\n");
	return (0);
}

/* int	main(int argc, char **argv) */
/* { */
/* 	t_dlist *list; */

/* 	list = NULL; */
/* 	for (int i = 1; i < argc; ++i) */
/* 		ft_dlstpush_back(&list, ft_strdup(argv[i])); */
	/* g_term.simplecmds = split_into_simple_cmds(g_term.args); */
	/* while (list) */
	/* { */
	/* ft_lstdisplay((t_list *)list, display); */
		/* ft_lstclear((t_list **)&list->content, free, free); */
		/* list = list->next; */
	/* } */
/* 	ft_dlstrewind(&list); */
/* 	ft_lstclear((t_list **)&list, free, free); */
/* 	ft_printf("\n"); */
/* 	return (0); */
/* } */
