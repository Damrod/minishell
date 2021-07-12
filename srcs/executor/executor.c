#include <libft.h>
#include <minishell0.h>
#include <sys/wait.h>

#define SIDE_OUT	0
#define SIDE_IN		1

t_simplcmd *simple(t_dlist *cmd)
{
	if (cmd)
		return ((t_simplcmd *)cmd->content);
	return (NULL);
}

int exec_cmd(t_dlist *cmd, char **env)
{
	pid_t	pid;
	int		ret;
	int		status;
	int		pipe_open;

	ret = EXIT_FAILURE;
	pipe_open = 0;
	if (simple(cmd)->type == TYPE_PIPE || (simple(cmd->prev) && simple(cmd->prev)->type == TYPE_PIPE))
	{
		pipe_open = 1;
		if (pipe(simple(cmd)->pipes))
			exit(1);
	}
	pid = fork();
	g_term.lastpid = pid;
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		if (dup2(simple(cmd)->infd, STDIN_FILENO) < 0)
			exit(1);
		if (dup2(simple(cmd)->outfd, STDOUT_FILENO) < 0)
			exit(1);
		if (simple(cmd)->type == TYPE_PIPE
			&& dup2(simple(cmd)->pipes[SIDE_IN], STDOUT_FILENO) < 0)
			exit(1);
		if (simple(cmd->prev) && simple(cmd->prev)->type == TYPE_PIPE
			&& dup2(simple(cmd->prev)->pipes[SIDE_OUT], STDIN_FILENO) < 0)
			exit(1);
		if (simple(cmd->prev) && simple(cmd->prev)->type == TYPE_PIPE)
			close(simple(cmd->prev)->pipes[SIDE_IN]);
		if ((ret = execve(simple(cmd)->args[0], simple(cmd)->args, env)) < 0)
			ft_dprintf(2, "error: cannot execute %s\n", simple(cmd)->args[0]);
		exit(ret);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (pipe_open)
		{
			close(simple(cmd)->pipes[SIDE_IN]);
			if (!simple(cmd->next))
				close(simple(cmd)->pipes[SIDE_OUT]);
		}
		if (simple(cmd->prev) && simple(cmd->prev)->type == TYPE_PIPE)
			close(simple(cmd->prev)->pipes[SIDE_OUT]);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	return (ret);
}
