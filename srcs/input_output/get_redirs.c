#include <libft.h>
#include <minishell0.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <error_mng.h>
#include <wstrcmp.h>
#include <get_tokens.h>

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
	size_t			i;
	unsigned char	type;
	char			*file;
	int				*prunepattern;
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
					uint32_t	heredocatline;

					heredocatline = g_term.lineno;
					result = NULL;
					ft_memset(array, '\0', sizeof(void *) * 4);
					while (get_next_line(0, &line) > 0
						   && ft_strncmp(line, file, ft_strlen(file) + 1))
					{
						g_term.lineno++;
						if(!result)
						{
							array[0] = line;
							array[1] = "\n";
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

					char		filepath[4098];

					make_non_existing_filename(filepath, sizeof(filepath));
					if (*input > STDIN_FILENO)
						close(*input);
					*input = open(filepath, O_CREAT|O_WRONLY, S_IRUSR|
								  S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
					if (*input == -1)
						return (error_file(file, prunepattern, args));
					write(*input, result, ft_strlen(result));
					close(*input);
					*input = open(filepath, O_RDONLY);
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
