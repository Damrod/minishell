#include <error_mng.h>

void	*clean_ptr(void **tofree0, void **tofree1, void **tofree2, void *retval)
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
	return (retval);
}

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

void	handle_noop(int sig)
{
	(void) sig;
}

void	handle_int(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_term.lastret = 1;
		return ;
	}
}

int	error_custom(void **freeme0, void **freeme1, void **freeme2, char *message)
{
	free_and_nullify(freeme0, freeme1, freeme2, 1);
	ft_dprintf(2, "%s: %s\n", EXENAME, message);
	return (1);
}
