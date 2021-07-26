#include "env.h"

int cleanup_exit(char ***env, t_dlist *cmd, int num)
{
	ft_dblptr_free((void **)*env);
	ft_dlstrewind(&cmd);
	comp_dtor(&cmd, NULL, 0);
	exit(num);
}

static int	exit_too_many_args(void)
{
	ft_dprintf(2, "%s: exit: too many arguments\n", EXENAME);
	return (1);
}

int	check_exit_arg(int num, char **args, char ***env, t_dlist *cmd)
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
			cleanup_exit(env, cmd, 2);
		}
		i++;
	}
	i = 0;
	while (args[++i])
		;
	if (i > 2)
		return (exit_too_many_args());
	else
		cleanup_exit(env, cmd, num);
	return (0);
}

int	ft_exit(char **args, char ***env, t_dlist *cmd)
{
	int	i;

	ft_dprintf(STDERR_FILENO, "exit\n");
	if (args[1])
	{
		i = ft_atoi(args[1]);
		return (check_exit_arg(i, args, env, cmd));
	}
	else
		cleanup_exit(env, cmd, EXIT_SUCCESS);
	return (0);
}
