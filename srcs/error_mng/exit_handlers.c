#include <libft.h>
#include <minishell0.h>

int	free_and_nullify(void **tofree0, void **tofree1, void **tofree2,
			int retvalue)
{
	if (tofree0)
	{
		free(*tofree0);
		*tofree0 = NULL;
	}
	if (tofree1)
	{
		free(*tofree1);
		*tofree1 = NULL;
	}
	if (tofree2)
	{
		free(*tofree2);
		*tofree2 = NULL;
	}
	return (retvalue);
}

void	handle_eot(int sig)
{
	extern char		**environ;

	(void) sig;
	free_and_nullify ((void **)&environ, NULL, NULL, 1);
	free_and_nullify((void **)&g_term.inputstring, NULL, NULL, 1);
	ft_printf("\n");
	exit(0);
}
