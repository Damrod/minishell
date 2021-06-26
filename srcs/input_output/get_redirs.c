#include <libft.h>
#include <minishell0.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <error_mng.h>
#include <wstrcmp.h>
#include <get_tokens.h>
#include <heredoc.h>

int	get_redirs(t_list **args, int *input, int *output)
{
	size_t			i;
	unsigned char	type;
	char			*file;
	int				*prunepattern;
	t_list			*list;

	prunepattern = ft_calloc(ft_lstsize(*args), sizeof(*prunepattern));
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
					error_syntax(file, prunepattern);
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
						return (error_file(file, prunepattern));
				}
				else if (!list->next)
					return (error_syntax("newline", prunepattern));
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
						return (error_file(file, prunepattern));
				}
				else if (!list->next)
					return (error_syntax("newline", prunepattern));
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
						return (error_file(file, prunepattern));
				}
				else if (!list->next)
					return (error_syntax("newline", prunepattern));
			}
			if (type == TYPE_HEREDOC)
			{
				if (list->next && list->next->content)
				{
					char *result;

					heredoc_getline(file, &result);
					if (heredoc_get_fd(result, input, file, prunepattern))
					{
						free (result);
						return (1);
					}
				}
				else if (!list->next)
					return (error_syntax("newline", prunepattern));
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
