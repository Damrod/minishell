#include <libft.h>

int	ft_puts(char *str)
{
	return (write(1, str, ft_strlen(str)));
}
