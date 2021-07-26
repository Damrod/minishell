#include <common.h>

t_term	g_term = {
	.environ = NULL,
	.lastret = 0,
};

static void	loop_commands(t_list *args, uint32_t *lineno)
{
	t_dlist			*simplecmds;
	t_dlist			*cmds;
	t_dlist			*cmdtable;

	simplecmds = ft_lstsplit(args, "|", get_pipes);
	cmdtable = build_cmd_table(&simplecmds, lineno);
	cmds = cmdtable;
	while (cmds)
	{
		g_term.lastret = exec_cmd(cmds);
		cmds = cmds->next;
	}
	comp_dtor(&cmdtable, NULL, 0);
}

static void	prompt_loop(void)
{
	char			*inputstring;
	t_list			*args;
	uint32_t		lineno;

	lineno = 0;
	while (1)
	{
		inputstring = readline("marishell% ");
		if (!inputstring)
		{
			ft_putstr_fd("exit", STDERR_FILENO);
			break ;
		}
		if (ft_strlen(inputstring) > 0)
			add_history(inputstring);
		lineno++;
		args = get_args(inputstring);
		free_and_nullify((void **)&inputstring, NULL, NULL, 1);
		if (!args)
			continue ;
		loop_commands(args, &lineno);
	}
}

int	main(int argc, char **argv)
{
	extern char		**environ;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	g_term.environ = ft_dblptr_cpy((const char **)environ, NULL, 1);
	signal(SIGINT, handle_int);
	signal(SIGQUIT, handle_noop);
	prompt_loop();
	ft_dblptr_free((void **)g_term.environ);
	ft_printf("\n");
	return (0);
}
