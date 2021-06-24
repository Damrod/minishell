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

void	free_and_nullify(void **tofree)
{
	free(*tofree);
	*tofree = NULL;
}

char	*downcast_wstr(const unsigned short *str, char is_low)
{
	char	*result;
	size_t	i;

	if (!str)
		return (NULL);
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

	if (checkdepth == CHECK_ANYQUOTE || checkdepth == CHECK_NOTQUOTE)
	{
		config_bitmasks(&bitmask, &bitmask2, CHECK_DBLQUOTE);
		config_bitmasks(&bitmask3, &bitmask4, CHECK_SNGQUOTE);
		aggregate = ((a & ~bitmask) == (b | bitmask2));
		aggregate = aggregate || ((a & ~bitmask3) == (b | bitmask4));
		if (checkdepth == CHECK_NOTQUOTE)
			return (!(aggregate));
		return (aggregate);
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
	free_and_nullify ((void **)&environ);
	free_and_nullify((void **)&g_term.inputstring);
	ft_printf("\n");
	exit(0);
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

char is_redir(unsigned short *arg)
{
	if (ft_wstrncmp(arg, ">", CHECK_NOTQUOTE, 2) == 0
		|| ft_wstrncmp(arg, "<", CHECK_NOTQUOTE, 2) == 0
		|| ft_wstrncmp(arg, ">>", CHECK_NOTQUOTE, 3) == 0
		|| ft_wstrncmp(arg, "<<", CHECK_NOTQUOTE, 3) == 0)
		return (1);
	return (0);
}

/* char is_pipe(unsigned short *arg) */
/* { */
/* 	if (ft_wstrncmp(arg, "|", CHECK_NOTQUOTE, 2) == 0) */
/* 		return (1); */
/* 	return (0); */
/* } */

/* char is_symbol(unsigned short *arg) */
/* { */
/* 	return (is_pipe(arg) || is_redir(arg)); */
/* } */

unsigned char	get_type(unsigned short *arg)
{
	unsigned char	type;

	if (ft_wstrncmp(arg, ">", CHECK_NOTQUOTE, 2) == 0)
		type = TYPE_OUT;
	else if (ft_wstrncmp(arg, ">>", CHECK_NOTQUOTE, 3) == 0)
		type = TYPE_APP;
	else if (ft_wstrncmp(arg, "<", CHECK_NOTQUOTE, 2) == 0)
		type = TYPE_IN;
	else if (ft_wstrncmp(arg, "<<", CHECK_NOTQUOTE, 3) == 0)
		type = TYPE_HEREDOC;
	else if (ft_wstrncmp(arg, "|", CHECK_NOTQUOTE, 2) == 0)
		type = TYPE_PIPE;
	else
		type = TYPE_END;
	return (type);
}

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

/* int	syntax_error(unsigned short *arg); */

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
/* 			return (syntax_error(arg)); */
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
/* 			return (syntax_error(arg)); */
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

/* int get_redirs(unsigned short **args, int *input, int *output) */
/* { */
/* 	t_list			*list; */
/* 	unsigned char 	type; */
/* 	char			*file; */
/* 	char			fileopen[TYPE_HEREDOC + 1]; */
/* 	int				*prunepattern; */
/* 	size_t			i; */
/* 	t_list			*lstorig; */

/* 	prunepattern = ft_calloc(ft_dblptrlen((void **)args), sizeof(*prunepattern)); */
/* 	*input = STDIN_FILENO; */
/* 	*output = STDOUT_FILENO; */
/* 	ft_memset(fileopen, 0, sizeof(fileopen)); */
/* 	i = 0; */
/* 	list = ft_arrtolst((void **)args, -1, NULL); */
/* 	lstorig = list; */
/* 	free(args); */
/* 	while (list) */
/* 	{ */
/* 		if (is_redir((unsigned short *)list->content)) */
/* 		{ */
/* 			type = get_type((unsigned short *)list->content); */
/* 			if (list->next && list->next->content) */
/* 				file = downcast_wstr(list->next->content, 1); */
/* 			if (type == TYPE_IN) */
/* 			{ */
/* 				if (list->next && list->next->content) */
/* 				{ */
/* 					if (fileopen[TYPE_IN]) */
/* 						close(*input); */
/* 					*input = open(file, O_RDONLY); */
/* 					free(file); */
/* 					fileopen[TYPE_IN] = 1; */
/* 					if (*input == -1) */
/* 						return (error_file(file, prunepattern, lstorig, errno)); */
/* 				} */
/* 				else if (!list->next) */
/* 					return (syntax_error(file, prunepattern, lstorig, list->content)); */
/* 			} */
/* 			if (type == TYPE_APP) */
/* 			{ */
/* 				if (list->next && list->next->content) */
/* 				{ */
/* 					if (fileopen[TYPE_APP]) */
/* 						close(*input); */
/* 					*output = open(file, O_CREAT|O_WRONLY|O_APPEND); */
/* 					fileopen[TYPE_APP] = 1; */
/* 					if (*input == -1) */
/* 						return (error_file(file, errno)); */
/* 				} */
/* 				else if (!list->next) */
/* 					return (syntax_error(file, list->content)); */
/* 			} */
/* 			if (type == TYPE_OUT) */
/* 			{ */
/* 				if (list->next && list->next->content) */
/* 				{ */
/* 					if (fileopen[TYPE_OUT]) */
/* 						close(*input); */
/* 					*output = open(file, O_CREAT|O_WRONLY|O_TRUNC); */
/* 					fileopen[TYPE_OUT] = 1; */
/* 					if (*input == -1) */
/* 						return (error_file(file, errno)); */
/* 				} */
/* 				else if (!list->next) */
/* 					return (syntax_error(file, list->content)); */
/* 			} */
/* 			if (type == TYPE_HEREDOC) */
/* 			{ */
/* 				if (list->next && list->next->content) */
/* 				{ */
/* 					char 	*line; */
/* 					char 	*result; */
/* 					char 	*tmp0; */
/* 					char 	*array[3]; */
/* 					char	isfirst; */
/* 					size_t	size; */

/* 					result = NULL; */
/* 					isfirst = 1; */
/* 					while (get_next_line(0, &line) > 0 */
/* 						   && ft_strncmp(line, file, ft_strlen(line) + 1)) */
/* 					{ */
/* 						if(isfirst) */
/* 						{ */
/* 							array[0] = line; */
/* 							array[1] = "\n"; */
/* 							size = 2; */
/* 							isfirst = 0; */
/* 						} */
/* 						else */
/* 						{ */
/* 							array[0] = result; */
/* 							array[1] = line; */
/* 							array[2] = "\n"; */
/* 							size = 3; */
/* 						} */
/* 						tmp0 = ft_strjoin_ult(size, array, ""); */
/* 						free(result); */
/* 						free(line); */
/* 						result = tmp0; */
/* 					} */
/* 					free (line); */
/* 					g_term.inputstring = result; */
/* 				} */
/* 				else if (!list->next) */
/* 					return (syntax_error(file, list->content)); */
/* 			} */
/* 			free(file); */
/* 			prunepattern[i++] = 1; */
/* 			prunepattern[i++] = 1; */
/* 			if (list) */
/* 				list = list->next->next; */
/* 		} */
/* 		else */
/* 		{ */
/* 			i++; */
/* 			if (list) */
/* 				list = list->next; */
/* 		} */
/* 	} */
/* 	ft_lstcullpat(&lstorig, prunepattern, free, free); */
/* 	free(prunepattern); */
/* 	list = lstorig; */
/* 	char *tmp; */
/* 	while(list) */
/* 	{ */
/* 		tmp = downcast_wstr(list->content, 1); */
/* 		free(list->content); */
/* 		list->content = tmp; */
/* 		list = list->next; */
/* 	} */
/* 	char **cmpcmd; */
/* 	cmpcmd = (char **)ft_lsttoarr(lstorig, NULL); */
/* 	ft_lstclear(&lstorig, NULL, free); */
/* 	return cmpcmd; */
/* } */

int	main(int argc, char **argv)
{
	t_list			*str;
	t_list			*orig;
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
			free_and_nullify((void **)&g_term.inputstring);
			break ;
		}
		str = get_args(g_term.inputstring);
		free_and_nullify((void **)&g_term.inputstring);
		if (!str)
			continue ;
		if (!na_calloc(ft_lstsize(str) + 1, sizeof(void *),
				(void **)&g_term.args))
		{
			free_and_nullify((void **)&g_term.inputstring);
			break ;
		}
		orig = str;
		i = 0;
		while (str)
		{
			const char *pipe = "|";
			/* const char *out = ">"; */
			/* const char *in = "<"; */
			/* const char *outappend = ">>"; */
			/* const char *heredoc = "<<"; */
			g_term.args[i] = downcast_wstr(str->content, 1);
			if (ft_wstrncmp(str->content, pipe, CHECK_NOTQUOTE, 2) == 0)
				ft_printf("This \"%s\" is a pipe\n", pipe);
			/* free_and_nullify ((void **)&g_term.inputstring); */
			str = str->next;
			i++;
		}
		ft_lstclear(&orig, free, free);
		apply_dblptr(g_term.args, print_dblptr);
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
