#include <libft.h>
#include <minishell0.h>

void	free_and_nullify(void **tofree)
{
	free(*tofree);
	*tofree = NULL;
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
