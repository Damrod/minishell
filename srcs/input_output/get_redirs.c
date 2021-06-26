#include <libft.h>
#include <minishell0.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <error_mng.h>
#include <wstrcmp.h>
#include <get_tokens.h>
#include <heredoc.h>

int	to_input(int *input, char *file, int *prunepattern, bool is_last)
{
	if (!is_last)
	{
		if (*input > STDIN_FILENO)
			close(*input);
		*input = open(file, O_RDONLY);
		if (*input == -1)
			return (error_file(file, prunepattern));
		return (0);
	}
	else
		return (error_syntax("newline", prunepattern));
}

int	to_append(int *output, char *file, int *prunepattern, bool is_last)
{
	if (!is_last)
	{
		if (*output > STDERR_FILENO)
			close(*output);
		*output = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (*output == -1)
			return (error_file(file, prunepattern));
		return (0);
	}
	else
		return (error_syntax("newline", prunepattern));
}

int	to_output(int *output, char *file, int *prunepattern, bool is_last)
{
	if (!is_last)
	{
		if (*output > STDERR_FILENO)
			close(*output);
		*output = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (*output == -1)
			return (error_file(file, prunepattern));
		return (0);
	}
	else
		return (error_syntax("newline", prunepattern));
}

int	to_heredoc(int *input, char *file, int *prunepattern, bool is_last)
{
	char	*result;

	if (!is_last)
	{
		heredoc_getline(file, &result);
		if (heredoc_get_fd(result, input, file, prunepattern))
		{
			free (result);
			return (1);
		}
		return (0);
	}
	else
		return (error_syntax("newline", prunepattern));
}

int	get_io_file(char **file, unsigned short *listcont,
			bool *islast, int *prunepattern)
{
	*islast = 0;
	*file = downcast_wstr(listcont, 1);
	if (is_symbol(listcont))
	{
		error_syntax(*file, prunepattern);
		free (*file);
		return (1);
	}
	return (0);
}

int	get_redirs(t_list **args, int *input, int *output)
{
	size_t			i;
	unsigned char	type;
	char			*file;
	int				*clpatt;
	t_list			*list;
	bool			is_last;

	clpatt = ft_calloc(ft_lstsize(*args), sizeof(*clpatt));
	i = 0;
	list = *args;
	while (list)
	{
		if (is_redir((unsigned short *)list->content))
		{
			is_last = 1;
			type = get_type((unsigned short *)list->content);
			if (list->next && list->next->content)
				if (get_io_file(&file, list->next->content, &is_last, clpatt))
					return (1);
			if (type == TYPE_IN)
				if (to_input(input, file, clpatt, is_last))
					return (1);
			if (type == TYPE_APP)
				if (to_append(output, file, clpatt, is_last))
					return (1);
			if (type == TYPE_OUT)
				if (to_output(output, file, clpatt, is_last))
					return (1);
			if (type == TYPE_HEREDOC)
				if (to_heredoc(input, file, clpatt, is_last))
					return (1);
			free(file);
			clpatt[i++] = 1;
			clpatt[i++] = 1;
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
	ft_lstcullpat(args, clpatt, free, free);
	free(clpatt);
	return (0);
}
