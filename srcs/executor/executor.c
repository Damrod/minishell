#include <executor.h>

static int	miniexec(char **args, char ***env, t_dlist *cmd)
{
	int			ret;
	char		**path;
	static char	*emptypath[2];

	emptypath[0] = "";
	emptypath[1] = NULL;
	path = emptypath;
	if (check_builtins(args, env, &ret, cmd) == -1)
	{
		path = read_path(*env);
		if (!path)
			path = emptypath;
		ret = check_path(args, path, env);
	}
	ft_dblptr_free((void **)*env);
	if (emptypath != path)
		ft_dblptr_free((void **)path);
	ft_dlstrewind(&cmd);
	comp_dtor(&cmd, NULL, 0);
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

static int	handle_parent(t_dlist *cmd, pid_t pid, bool pipe_open, char ***env)
{
	int			status;
	int			ret;

	signal(SIGINT, handle_noop);
	if (pid != waitpid(pid, &status, 0))
		exit(quit_exec(EXIT_FAILURE, "waitpid", cmd, env));
	signal(SIGINT, handle_int);
	if (pipe_open)
	{
		if (close(simple(cmd)->pipes[SIDE_IN]))
			exit(quit_exec(EXIT_FAILURE, "close", cmd, env));
		if (!simple(cmd->next))
			if (close(simple(cmd)->pipes[SIDE_OUT]))
				exit(quit_exec(EXIT_FAILURE, "close", cmd, env));
	}
	if (cmd->prev && simple(cmd->prev)->type == TYPE_PIPE)
		if (close(simple(cmd->prev)->pipes[SIDE_OUT]))
			exit(quit_exec(EXIT_FAILURE, "close", cmd, env));
	if (is_internal(simple(cmd)->args[0]) && !cmd->prev && !cmd->next)
		return (check_builtins(simple(cmd)->args, env, &ret, cmd));
	return (handle_signals(status));
}

static int	handle_child(t_dlist *cmd, char ***env)
{
	if (is_internal(simple(cmd)->args[0]) && !cmd->prev && !cmd->next)
		cleanup_exit(env, cmd, EXIT_SUCCESS);
	if (simple(cmd)->type == TYPE_PIPE)
		my_dup2(simple(cmd)->pipes[SIDE_IN], STDOUT_FILENO, cmd);
	if (cmd->prev && simple(cmd->prev)->type == TYPE_PIPE)
		my_dup2(simple(cmd->prev)->pipes[SIDE_OUT], STDIN_FILENO, cmd);
	my_dup2(simple(cmd)->infd, STDIN_FILENO, cmd);
	my_dup2(simple(cmd)->outfd, STDOUT_FILENO, cmd);
	exit(miniexec(simple(cmd)->args, env, cmd));
}

int	exec_cmd(t_dlist *cmd, char ***env)
{
	int			pipe_open;
	pid_t		pid;

	pipe_open = 0;
	if (simple(cmd)->type == TYPE_PIPE || (simple(cmd->prev)
			&& simple(cmd->prev)->type == TYPE_PIPE))
	{
		pipe_open = 1;
		if (pipe(simple(cmd)->pipes))
			exit(quit_exec(EXIT_FAILURE, "pipe", cmd, env));
	}
	pid = fork();
	if (pid < 0)
		exit(quit_exec(EXIT_FAILURE, "fork", cmd, env));
	else
	{
		if (pid == 0)
			return (handle_child(cmd, env));
		else
			return (handle_parent(cmd, pid, pipe_open, env));
	}
}
