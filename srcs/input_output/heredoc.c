#include <heredoc.h>

static void	make_hash(char *hash, size_t size, const char *str)
{
	static char	alpha[62] = "abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	size_t		i;
	uint32_t	len;

	len = ft_strlen(str);
	i = 0;
	while (i < len && i < size - 1)
	{
		hash[i] = alpha[ft_random((uint32_t)(((uint32_t)str[i] << 8)
					^ 0x6D00)) % 62];
		i++;
	}
	hash[i] = '\0';
}

static int	make_non_existing_filename(char *filepath, size_t size,
			const char *str)
{
	char		hash[6];
	struct stat	f_stat;
	size_t		i;

	if (!str)
		str = "ROaTH0gDd7";
	ft_memset(filepath, '\0', size);
	i = 0;
	while (i < 2048)
	{
		make_hash(hash, sizeof(hash), str);
		ft_snprintf(filepath, size - 1, "/tmp/tmp.%s", hash);
		if (stat(filepath, &f_stat) != 0)
			return (0);
		i++;
	}
	return (1);
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

	if (make_non_existing_filename(filepath, sizeof(filepath), result))
		return (error_custom((void **)&file, (void **)&prunepattern, NULL,
				"here-doc couldn't create file"));
	if (*input > STDIN_FILENO)
		close(*input);
	*input = open(filepath, O_CREAT | O_WRONLY, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (*input == -1)
		return (error_file(file, prunepattern));
	if (result)
		write(*input, result, ft_strlen(result));
	close(*input);
	*input = open(filepath, O_RDONLY);
	unlink(filepath);
	free(result);
	printf("%s\n", filepath);
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
