#include <builtins.h>

int	ft_echo(char **args)
{
	int			i;
	int			flag;

	flag = 0;
	i = 0;
	if (args[0] && ft_strncmp("-n", args[0], 3) == 0)
	{
		flag = 1;
		++i;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[++i])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
