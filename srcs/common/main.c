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
#include <stdbool.h>

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
		*bitmask = 0xFF00U;
		*bitmask2 = 0;
	}
	if (checkdepth == CHECK_SNGQUOTE)
	{
		*bitmask = (FLAG_CIGNORE | FLAG_ESCAPED | FLAG_NOTSPCE | FLAG_DBLQUOT);
		*bitmask2 = FLAG_SNGQUOT;
	}
	if (checkdepth == CHECK_DBLQUOTE)
	{
		*bitmask = (FLAG_CIGNORE | FLAG_ESCAPED | FLAG_NOTSPCE | FLAG_SNGQUOT);
		*bitmask2 = FLAG_DBLQUOT;
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
	bool			aggregate;

	if (checkdepth == CHECK_ANYQUOTE || checkdepth == CHECK_NOTQUOTE)
	{
		aggregate = ((a & FLAG_DBLQUOT) | (a & FLAG_SNGQUOT));
		if (checkdepth == CHECK_NOTQUOTE)
			aggregate = !aggregate;
		aggregate &= ((a & 0xFF) == (b & 0xFF));
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

char is_pipe(unsigned short *arg)
{
	if (ft_wstrncmp(arg, "|", CHECK_NOTQUOTE, 2) == 0)
		return (1);
	return (0);
}

char is_symbol(unsigned short *arg)
{
	return (is_pipe(arg) || is_redir(arg));
}

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

int error_syntax(char *token, int *prunepattern, t_list **args)
{
	free(prunepattern);
	ft_lstclear(args, free, free);
	ft_dprintf(2, "%s: syntax error near unexpected token `%s'\n", EXENAME, token);
	return (1);
}

int warning_shell(char *token, uint32_t line)
{
	ft_dprintf(1, "%s: warning: here-document at line %u delimited by "
			   "end-of-file (wanted `%s')\n", EXENAME, line, token);
	return (1);
}

int error_file(char *file, int *prunepattern, t_list **args)
{
	int		error;

	error = errno;
	free(prunepattern);
	ft_lstclear(args, free, free);
	ft_dprintf(2, "%s: %s: %s\n", EXENAME, file, strerror(error));
	free(file);
	return (1);
}

#include <sys/stat.h>
#include <stdbool.h>


bool	file_exists (char *filename)
{
	struct stat	buffer;

	return (stat (filename, &buffer) == 0);
}

void	make_non_existing_filename(char *filepath, size_t size)
{
	char	buffer[2048];
	size_t	i;
	char	cwd[2048];

	ft_memset(filepath, '\0', size);
	ft_memset(buffer, '\0', sizeof(*buffer));
	ft_memset(cwd, '\0', sizeof(*cwd));
	i = 0;
	while (i < (sizeof(buffer) - 1))
	{
		buffer[i] = 'a' + (i % 26);
		buffer[i + 1] = '\0';
		ft_snprintf(filepath, size - 1, "/tmp/%s", buffer);
		if (!file_exists(filepath))
			return ;
		i++;
	}
	return ;
}
int	get_redirs(t_list **args, int *input, int *output)
{
	unsigned char	type;
	char			*file;
	int				*prunepattern;
	size_t			i;
	t_list			*list;

	prunepattern = ft_calloc(ft_lstsize(*args), sizeof(*prunepattern));
	*input = STDIN_FILENO;
	*output = STDOUT_FILENO;
	i = 0;
	list = *args;
	while (list)
	{
		if (is_redir((unsigned short *)list->content))
		{
			type = get_type((unsigned short *)list->content);
			if (list->next && list->next->content)
			{
				file = downcast_wstr(list->next->content, 1);
				if (is_symbol(list->next->content))
				{
					error_syntax(file, prunepattern, args);
					free (file);
					return (1);
				}
			}
			if (type == TYPE_IN)
			{
				if (list->next && list->next->content)
				{
					if (*input > STDIN_FILENO)
						close(*input);
					*input = open(file, O_RDONLY);
					if (*input == -1)
						return (error_file(file, prunepattern, args));
				}
				else if (!list->next)
					return (error_syntax("newline", prunepattern, args));
			}
			if (type == TYPE_APP)
			{
				if (list->next && list->next->content)
				{
					if (*output > STDERR_FILENO)
						close(*output);
					*output = open(file, O_CREAT|O_WRONLY|O_APPEND, S_IRUSR|
								   S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
					if (*output == -1)
						return (error_file(file, prunepattern, args));
				}
				else if (!list->next)
					return (error_syntax("newline", prunepattern, args));
			}
			if (type == TYPE_OUT)
			{
				if (list->next && list->next->content)
				{
					if (*output > STDERR_FILENO)
						close(*output);
					*output = open(file, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|
								   S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
					if (*output == -1)
						return (error_file(file, prunepattern, args));
				}
				else if (!list->next)
					return (error_syntax("newline", prunepattern, args));
			}
			if (type == TYPE_HEREDOC)
			{
				if (list->next && list->next->content)
				{
					char		*line;
					char		*result;
					char		*tmp0;
					char		*array[4];
					char		isfirst;
					char		filepath[4098];
					uint32_t	heredocatline;

					heredocatline = g_term.lineno;
					result = NULL;
					isfirst = 1;
					ft_memset(array, '\0', sizeof(void *) * 4);
					while (get_next_line(0, &line) > 0
						   && ft_strncmp(line, file, ft_strlen(file) + 1))
					{
						g_term.lineno++;
						if(isfirst)
						{
							array[0] = line;
							array[1] = "\n";
							isfirst = 0;
						}
						else
						{
							array[0] = result;
							array[1] = line;
							array[2] = "\n";
						}
						tmp0 = ft_strjoin_ult(-1, (const char **)array, "");
						free(result);
						free(line);
						result = tmp0;
					}
					if (ft_strncmp(line, file, ft_strlen(file) + 1))
						warning_shell(file, heredocatline);
					free (line);
					if (*input > STDIN_FILENO)
						close(*input);
					make_non_existing_filename(filepath, sizeof(filepath));
					*input = open(filepath, O_CREAT|O_WRONLY, S_IRUSR|
								  S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
					if (*input == -1)
						return (error_file(file, prunepattern, args));
					write(*input, result, ft_strlen(result));
					close(*input);
					*input = open(filepath, O_RDONLY, S_IRUSR|
									  S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
					unlink(filepath);
					free(result);
				}
				else if (!list->next)
					return (error_syntax("newline", prunepattern, args));
			}
			free(file);
			prunepattern[i++] = 1;
			prunepattern[i++] = 1;
			if (list && list->next)
				list = list->next->next;
		}
		else
		{
			i++;
			if (list)
				list = list->next;
		}
	}
	ft_lstcullpat(args, prunepattern, free, free);
	free(prunepattern);
	return (0);
}

int	main(int argc, char **argv)
{
	t_list			*str;
	t_list			*orig;
	size_t			i;
	extern char		**environ;
	char			*tmp;

	(void)argc;
	(void)argv;
	environ = ft_dblptr_cpy((const char **)environ, NULL, 0);
	str = NULL;
	g_term.lastret = 0;
	signal(SIGINT, handle_eot);
	signal(SIGQUIT, handle_eot);
	g_term.lineno = 0;
	while (1)
	{
		g_term.inputstring = readline("marishell% ");
		g_term.lineno++;
		if (g_term.inputstring && g_term.inputstring[0] == STX)
		{
			free_and_nullify((void **)&g_term.inputstring);
			break ;
		}
		str = get_args(g_term.inputstring);
		free_and_nullify((void **)&g_term.inputstring);
		if (!str)
			continue ;
		g_term.lastret = get_redirs(&str, &g_term.infd, &g_term.outfd);
		if (g_term.infd > STDERR_FILENO)
		{
			char *line;

			while(get_next_line(g_term.infd, &line) > 0)
			{
				ft_printf("%s\n", line);
				free (line);
			}
			ft_printf("%s\n", line);
			free (line);
		}
		if (g_term.infd > STDERR_FILENO)
			close(g_term.infd);
		if (g_term.outfd > STDERR_FILENO)
			close(g_term.outfd);
		if (g_term.lastret)
			continue;
		orig = str;
		i = 0;
		while (str)
		{
			tmp = downcast_wstr(str->content, 1);
			ft_printf("%s\n", tmp);
			free(tmp);
			str = str->next;
			i++;
		}
		ft_lstclear(&orig, free, free);
		/* apply_dblptr(g_term.args, print_dblptr); */
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
