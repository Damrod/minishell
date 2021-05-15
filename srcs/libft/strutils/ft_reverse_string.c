#include "libft.h"

void	ft_reverse_string(char *buf)
{
	size_t	len;
	size_t	len2;
	char	c;

	len = ft_strlen(buf);
	len--;
	len2 = len;
	while (len > len2 / 2)
	{
		c = buf[len2 - len];
		buf[len2 - len] = buf[len];
		buf[len] = c;
		len--;
	}
}
