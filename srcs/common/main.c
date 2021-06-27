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

t_term	g_term = {
	.environ = NULL,
	.args = NULL,
	.cmds = NULL,
	.inputstring = NULL,
	.lineno = 0,
	.infd = STDIN_FILENO,
	.outfd = STDOUT_FILENO,
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

t_list	*split_into_simple_cmds(t_list *compcmd)
{
	return (ft_lstsplit(compcmd, "|", get_pipes));
}

void	display(void *str, int i)
{
	char *arg;

	arg = downcast_wstr(str, 1);
	ft_printf("%d, %s\n", i, arg);
	free (arg);
}

int	main(int argc, char **argv)
{
	t_list			*str;
	t_list			*orig;
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
		g_term.lineno++;
		if (g_term.inputstring && g_term.inputstring[0] == STX)
		{
			free_and_nullify((void **)&g_term.inputstring, NULL, NULL, 1);
			break ;
		}
		str = get_args(g_term.inputstring);
		free_and_nullify((void **)&g_term.inputstring, NULL, NULL, 1);
		if (!str)
			continue ;

		/* str = split_into_simple_cmds(str); */

		g_term.lastret = get_redirs(&str, &g_term.infd, &g_term.outfd);
		if (g_term.infd > STDERR_FILENO)
		{
			char *line;

			while (get_next_line(g_term.infd, &line) > 0)
			{
				ft_printf("%s\n", line);
				free (line);
			}
			ft_printf("%s\n", line);
			free_and_nullify((void **)&line, NULL, NULL, 1);
		}
		if (g_term.infd > STDERR_FILENO)
			close(g_term.infd);
		if (g_term.outfd > STDERR_FILENO)
			close(g_term.outfd);
		if (g_term.lastret)
		{
			ft_lstclear(&str, free, free);
			continue ;
		}

		/* orig = str; */
		/* while (str) */
		/* { */
		/* 	ft_lstdisplay(str->content, display); */
		/* 	ft_lstclear((t_list **)&str->content, free, free); */
		/* 	str = str->next; */
		/* } */
		/* ft_lstclear(&orig, NULL, free); */

		char *tmp2;
		orig = str;
		while (str)
		{
			tmp2 = downcast_wstr(str->content, 1);
			printf("%s\n", tmp2);
			free(tmp2);
			str = str->next;
		}
		ft_lstclear(&orig, free, free);

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
