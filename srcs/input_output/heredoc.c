#include <heredoc.h>

static bool	file_exists (char *filename)
{
	struct stat	buffer;

	return (stat (filename, &buffer) == 0);
}

static void	make_non_existing_filename(char *filepath, size_t size)
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

static void	setup_buffer(char **array, char *result, char *line, size_t size)
{
	static char	*newline = "\n";

	if (size == 2)
	{
		array[0] = line;
		array[1] = newline;
	}
	else if (size == 3)
	{
		array[0] = result;
		array[1] = line;
		array[2] = newline;
	}
}

int	heredoc_get_fd(char *result, int *input, char *file, int *prunepattern)
{
	char		filepath[4098];

	make_non_existing_filename(filepath, sizeof(filepath));
	if (*input > STDIN_FILENO)
		close(*input);
	*input = open(filepath, O_CREAT | O_WRONLY, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (*input == -1)
		return (error_file(file, prunepattern));
	write(*input, result, ft_strlen(result));
	close(*input);
	*input = open(filepath, O_RDONLY);
	unlink(filepath);
	free(result);
	return (0);
}

int	heredoc_getline(char *file, char **result)
{
	char		*line;
	char		*tmp0;
	char		*array[4];
	uint32_t	heredocatline;

	heredocatline = g_term.lineno;
	*result = NULL;
	ft_memset(array, '\0', sizeof(void *) * 4);
	while (get_next_line(0, &line) > 0
		&& ft_strncmp(line, file, ft_strlen(file) + 1))
	{
		g_term.lineno++;
		if (!*result)
			setup_buffer(array, NULL, line, 2);
		else
			setup_buffer(array, *result, line, 3);
		tmp0 = ft_strjoin_ult(-1, (const char **)array, ""); // unprot malloc
		free(*result);
		free(line);
		*result = tmp0;
	}
	if (ft_strncmp(line, file, ft_strlen(file) + 1))
		warning_shell(file, heredocatline);
	free (line);
	return (0);
}
