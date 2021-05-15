#include <libft.h>

void	ft_wrtptr(char *c, char *str)
{
	size_t	size;

	size = ft_strlen(str);
	while (size > 0)
	{
		*c = *str;
		c++;
		str++;
		size--;
	}
}
