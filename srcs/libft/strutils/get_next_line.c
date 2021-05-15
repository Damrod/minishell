/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:07:06 by aollero-          #+#    #+#             */
/*   Updated: 2020/09/28 11:27:31 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

ssize_t	na_read(int fd, void *buf, size_t count, ssize_t *ret_val)
{
	return (*ret_val = read(fd, buf, count));
}

char	*na_strchr(const char *str, int c, char **ret_val)
{
	return (*ret_val = ft_strchr(str, c));
}

static int	next_line(char **line, char **remain, ssize_t bt_rd)
{
	char	*aux;
	char	*newl;

	if (bt_rd < 0)
		return (-1);
	if ((!bt_rd && !(*remain)) || !na_strchr(*remain, '\n', & newl))
	{
		if (!bt_rd && !(*remain))
			*line = ft_strdup("");
		else
		{
			*line = *remain;
			*remain = NULL;
		}
		return (0);
	}
	else
	{
		*newl = 0;
		*line = ft_strdup(*remain);
		aux = ft_strdup(newl + 1);
		free(*remain);
		*remain = aux;
		return (1);
	}
}

int	get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*remainder[MAX_FD] = {NULL};
	long int		bytes_read;
	char			*aux;

	if ((!line || fd < 0 || BUFFER_SIZE < 1
			|| !(na_malloc(BUFFER_SIZE + 1, (void **) & buff))
			|| (read(fd, buff, 0) < 0)))
		return (-1);
	while (na_read(fd, buff, BUFFER_SIZE, & bytes_read) > 0)
	{
		*(buff + bytes_read) = 0;
		if (!(*(remainder + fd)))
			*(remainder + fd) = ft_strdup(buff);
		else
		{
			aux = ft_strjoin(*(remainder + fd), buff);
			free(*(remainder + fd));
			*(remainder + fd) = aux;
		}
		if (ft_strchr(*(remainder + fd), '\n'))
			break ;
	}
	free(buff);
	return (next_line(line, remainder + fd, bytes_read));
}
