#include <libft.h>
#include <minishell0.h>

int	free_and_nullify(void **tofree)
{
	if (tofree)
	{
		free(*tofree);
		*tofree = NULL;
	}
	return (1);
}

void	handle_eot(int sig)
{
	extern char		**environ;

	(void) sig;
	free_and_nullify ((void **)&environ);
	free_and_nullify((void **)&g_term.inputstring);
	ft_printf("\n");
	exit(0);
}
