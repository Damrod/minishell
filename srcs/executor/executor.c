#include <executor.h>

static int	miniexec(char **args)
{
	int			ret;
	char		**path;
	static char	*emptypath[2];

	emptypath[0] = "";
	emptypath[1] = NULL;
	path = emptypath;
	if (check_builtins(args, &g_term.environ, &ret) == -1)
	{
		path = read_path(g_term.environ);
		if (!path)
			path = emptypath;
		ret = check_path(args, path);
	}
	ft_dblptr_free((void **)g_term.environ);
	if (emptypath != path)
		ft_dblptr_free((void **)path);
	return (ret);
}

static int	handle_signals(int status)
{
	int	ret;

	ret = EXIT_FAILURE;
	if (WIFSIGNALED(status))
	{
		ret = 130;
		if (WTERMSIG(status) == SIGINT)
			ft_printf("\n");
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_dprintf(2, "Quit ");
			ret = 131;
		}
		if (WTERMSIG(status) == SIGKILL)
		{
			ft_dprintf(2, "Killed\n");
			ret = 137;
		}
		if (WCOREDUMP(status))
			ft_dprintf(2, "(core dumped)\n");
	}
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}

static int	handle_parent(t_dlist *cmd, pid_t pid, bool pipe_open)
{
	int			status;
	int			ret;

	signal(SIGINT, handle_noop);
	if (pid != waitpid(pid, &status, 0))
		exit(quit_exec(EXIT_FAILURE, "waitpid", cmd));
	signal(SIGINT, handle_int);
	if (pipe_open)
	{
		if (close(simple(cmd)->pipes[SIDE_IN]))
			exit(quit_exec(EXIT_FAILURE, "close", cmd));
		if (!simple(cmd->next))
			if (close(simple(cmd)->pipes[SIDE_OUT]))
				exit(quit_exec(EXIT_FAILURE, "close", cmd));
	}
	if (cmd->prev && simple(cmd->prev)->type == TYPE_PIPE)
		if (close(simple(cmd->prev)->pipes[SIDE_OUT]))
			exit(quit_exec(EXIT_FAILURE, "close", cmd));
	if (is_internal(simple(cmd)->args[0]) && !cmd->prev && !cmd->next)
		return (check_builtins(simple(cmd)->args,
				&g_term.environ, &ret));
	return (handle_signals(status));
}

static int	handle_child(t_dlist *cmd)
{
	if (is_internal(simple(cmd)->args[0]) && !cmd->prev && !cmd->next)
		exit (0);
	if (simple(cmd)->type == TYPE_PIPE)
		my_dup2(simple(cmd)->pipes[SIDE_IN], STDOUT_FILENO, EXIT_FAILURE, cmd);
	if (cmd->prev && simple(cmd->prev)->type == TYPE_PIPE)
		my_dup2(simple(cmd->prev)->pipes[SIDE_OUT], STDIN_FILENO,
			EXIT_FAILURE, cmd);
	my_dup2(simple(cmd)->infd, STDIN_FILENO, EXIT_FAILURE, cmd);
	my_dup2(simple(cmd)->outfd, STDOUT_FILENO, EXIT_FAILURE, cmd);
	exit(miniexec(simple(cmd)->args));
}

int	exec_cmd(t_dlist *cmd)
{
	int			pipe_open;
	pid_t		pid;

	g_term.lastret = EXIT_FAILURE;
	pipe_open = 0;
	if (simple(cmd)->type == TYPE_PIPE || (simple(cmd->prev)
			&& simple(cmd->prev)->type == TYPE_PIPE))
	{
		pipe_open = 1;
		if (pipe(simple(cmd)->pipes))
			exit(quit_exec(EXIT_FAILURE, "pipe", cmd));
	}
	pid = fork();
	if (pid < 0)
		exit(quit_exec(EXIT_FAILURE, "fork", cmd));
	else
	{
		if (pid == 0)
			g_term.lastret = handle_child(cmd);
		else
			g_term.lastret = handle_parent(cmd, pid, pipe_open);
	}
	return (g_term.lastret);
}
