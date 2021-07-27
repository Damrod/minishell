#include <minishell.h>
#include <wstrcmp.h>

void	print_dblptr(const char *input)
{
	printf("%s\n", input);
}

int	get_pipes(void *src, void *key)
{
	unsigned short	*a;
	char			*b;

	a = src;
	b = key;
	return (ft_wstrncmp(a, b, CHECK_NOTQUOTE, 2));
}

int	quit_exec(int retstatus, char *sysc, t_dlist *cmds, char ***env)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", EXENAME, sysc, strerror(errno));
	ft_dlstrewind(&cmds);
	comp_dtor(&cmds, NULL, 0);
	ft_dblptr_free((void **)*env);
	*env = NULL;
	return (retstatus);
}

int	is_internal(char *arg)
{
	if (ft_strcmp(arg, "export") == 0 || ft_strcmp(arg, "unset") == 0
		|| ft_strcmp(arg, "exit") == 0 || ft_strcmp(arg, "cd") == 0)
		return (1);
	return (0);
}

void	my_dup2(int oldfd, int newfd, t_dlist *cmds, char ***env)
{
	if (dup2(oldfd, newfd) < 0)
		exit(quit_exec(EXIT_FAILURE, "dup2", cmds, env));
}
