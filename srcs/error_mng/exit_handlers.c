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

	(void) environ;
	(void) sig;
	if (sig == SIGINT)
	{
		if (g_term.lastpid > 0)
		{
			kill(g_term.lastpid, SIGINT);
			g_term.lastpid = 0;
			return ;
		}
		ft_printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_term.lastret = 1;
		return ;
	}
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		if (g_term.lastpid > 0)
		{
			ft_printf("Quit (core dumped) %d\n", g_term.lastpid);
			kill(g_term.lastpid, SIGQUIT);
			g_term.lastpid = 0;
		}
	}
}
