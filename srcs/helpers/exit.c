#include "env.h"

void	check_exit_arg(int num, char **args)
{
	int	i;

	i = 0;
	if (ft_strncmp(args[1], "-", 1) == 0)
		i++;
	while (args[1][i])
	{
		if (ft_isdigit(args[1][i]) != 1)
		{
			ft_dprintf(2, "%s: exit: %s: numeric argument required\n", EXENAME,
				args[1]);
			exit(2);
		}
		i++;
	}
	i = 0;
	while (args[++i])
		;
	if (i > 2)
		ft_dprintf(2, "%s: exit: too many arguments\n", EXENAME);
	else
		exit (num);
}

int	ft_exit(char **args)
{
	int	i;

	printf("exit\n");
	if (args[1])
	{
		i = ft_atoi(args[1]);
		check_exit_arg(i, args);
	}
	else
		exit (g_term.lastret);
	return (0);
}
