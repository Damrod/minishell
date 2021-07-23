#include <libft.h>

static ssize_t	na_read(int fd, void *buf, size_t count, ssize_t *ret_val)
{
	return (*ret_val = read(fd, buf, count));
}

static char	*ft_straddchr(char *str, char c)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	result = malloc (i + 2);
	i = 0;
	while (str[i])
		result[j++] = str[i++];
	result[j++] = c;
	result[j] = '\0';
	free (str);
	return (result);
}

typedef struct s_char_set {
	const char	*charset;
	uint16_t	size;
}	t_charset;

static void	makeunion(t_charset *charset)
{
	char		buffer[256];
	char		*chars;
	uint16_t	i;
	uint16_t	j;

	ft_memset(buffer, '\0', sizeof(buffer));
	i = 0;
	j = 0;
	while (i < charset->size)
	{
		if (!ft_memchr(buffer, charset->charset[i], charset->size))
		{
			buffer[j] = charset->charset[i];
			j++;
		}
		i++;
	}
	chars = malloc(j);
	memcpy(chars, buffer, j);
	charset->charset = chars;
	charset->size = j;
}

int	get_next_line_check_input(int fd, char **line, const char *charset,
							uint16_t cssize)
{
	ssize_t		ret;
	uint8_t		buf;
	t_charset	cset;

	if (!line || !(na_malloc(1, (void **)line)))
		return (-1);
	**line = '\0';
	cset.charset = charset;
	cset.size = cssize;
	makeunion(&cset);
	while ((na_read(fd, &buf, 1, &ret)) > 0)
	{
		if (ft_memchr(cset.charset, buf, cset.size))
			break ;
		*line = ft_straddchr(*line, buf);
		if (!*line)
			return (-1);
	}
	free ((void *)cset.charset);
	return (ret);
}
