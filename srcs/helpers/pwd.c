#include <builtins.h>

int	ft_pwd(void)
{
	char	*buff;

	buff = malloc(1024);
	getcwd(buff, 1024);
	ft_putstr_fd(buff, 1);
	ft_putchar_fd('\n', 1);
	free(buff);
	return (0);
}
