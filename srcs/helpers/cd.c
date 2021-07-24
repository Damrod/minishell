#include <builtins.h>
#include <env.h>
#include <error_mng.h>

int	ft_cd(char **args)
{
	char	*path;

	path = args[0];
	if (path && args[1])
		return (error_cmd("cd", NULL, "too many arguments", 1));
	if (!path)
		chdir(ft_getenv("HOME"));
	else
	{
		if (-1 == chdir(path))
			return (error_cmd("cd", path, NULL, 1));
	}
	return (0);
}
