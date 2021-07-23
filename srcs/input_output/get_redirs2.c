#include <get_redirs2.h>

int	to_input(int *input, char *file, bool is_last)
{
	if (!is_last)
	{
		if (*input > STDIN_FILENO)
			if (close(*input))
				return (1);
		*input = open(file, O_RDONLY);
		if (*input == -1)
			return (error_file(file));
		return (0);
	}
	else
		return (error_syntax("newline"));
}

int	to_append(int *output, char *file, bool is_last)
{
	if (!is_last)
	{
		if (*output > STDERR_FILENO)
			if (close(*output))
				return (1);
		*output = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (*output == -1)
			return (error_file(file));
		return (0);
	}
	else
		return (error_syntax("newline"));
}

int	to_output(int *output, char *file, bool is_last)
{
	if (!is_last)
	{
		if (*output > STDERR_FILENO)
			if (close(*output))
				return (1);
		*output = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (*output == -1)
			return (error_file(file));
		return (0);
	}
	else
		return (error_syntax("newline"));
}

int	to_heredoc(int *input, char *file, bool is_last)
{
	char	*result;

	if (!is_last)
	{
		heredoc_getline(file, &result);
		if (heredoc_get_fd(result, input, file))
		{
			free (result);
			return (1);
		}
		return (0);
	}
	else
		return (error_syntax("newline"));
}

int	get_io_file(char **file, unsigned short *listcont, bool *islast)
{
	*islast = 0;
	*file = downcast_wstr(listcont, 1);
	if (is_symbol(listcont))
	{
		error_syntax(*file);
		free (*file);
		return (1);
	}
	return (0);
}
