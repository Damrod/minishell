#include <env.h>

int	check_builtins(char **args, char ***env, int *ret)
{
	if (ft_strcmp(args[0], "export") == 0)
		return (*ret = ft_export(env, args));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (*ret = ft_echo(&args[1]));
	else if (ft_strcmp(args[0], "env") == 0)
		return (*ret = ft_env(*env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (*ret = ft_unset(env, args));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (*ret = ft_exit(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (*ret = ft_cd(&args[1], env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (*ret = ft_pwd());
	return (*ret = -1);
}

t_simplcmd	*simple(t_dlist *cmd)
{
	if (cmd)
		return ((t_simplcmd *)cmd->content);
	return (NULL);
}
