#include <libft.h>
#include <minishell0.h>
#include <minishell.h>
#include <sys/wait.h>

#define SIDE_OUT	0
#define SIDE_IN		1

//esto a libft o common(?)
static int	ft_strcmp(char *s1, char *s2)
{
	while (*s2 == *s1 && *s1)
	{
		s2++;
		s1++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	check_builtins(char **args, char ***env)
{
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(env, args));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(&args[1]));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(*env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(env, args));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(&args[1]));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	return (-1);
}

int	is_internal(char *arg)
{
	if (ft_strcmp(arg, "export") == 0 || ft_strcmp(arg, "unset") == 0
		|| ft_strcmp(arg, "exit") == 0 || ft_strcmp(arg, "cd") == 0)
		return (1);
	return (0);
}

#include <stdbool.h>

int	miniexec(char **args)
{
	int			ret;

	if((ret = (check_builtins(args, &g_term.environ))) == -1)
	{
		ret = check_path(args, g_term.path);
	}
	ft_dblptr_free((void **)g_term.environ);
	return (ret);
}

t_simplcmd *simple(t_dlist *cmd)
{
	if (cmd)
		return ((t_simplcmd *)cmd->content);
	return (NULL);
}

void	my_dup2(int oldfd, int newfd, int retstatus)
{
	if (dup2(oldfd, newfd) < 0)
	{
		ft_dblptr_free((void **)g_term.environ);
		exit (retstatus);
	}
}

int	handle_parent(t_dlist *cmd, bool pipe_open)
{
	extern char	**environ;
	int			status;
	int			ret;

	ret = EXIT_FAILURE;
	waitpid(g_term.lastpid, &status, 0);
	if (pipe_open)
	{
		close(simple(cmd)->pipes[SIDE_IN]);
		if (!simple(cmd->next))
			close(simple(cmd)->pipes[SIDE_OUT]);
	}
	if (cmd->prev && simple(cmd->prev)->type == TYPE_PIPE)
		close(simple(cmd->prev)->pipes[SIDE_OUT]);
	if (is_internal(simple(cmd)->args[0]) && !cmd->prev)
		return (g_term.lastret = check_builtins(simple(cmd)->args, &environ));
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}

int handle_child(t_dlist *cmd)
{
	if (is_internal(simple(cmd)->args[0]) && !cmd->prev)
		exit (0);
	if (simple(cmd)->type == TYPE_PIPE)
		my_dup2(simple(cmd)->pipes[SIDE_IN], STDOUT_FILENO, EXIT_FAILURE);
	if (cmd->prev && simple(cmd->prev)->type == TYPE_PIPE)
		my_dup2(simple(cmd->prev)->pipes[SIDE_OUT], STDIN_FILENO, EXIT_FAILURE);
	my_dup2(simple(cmd)->infd, STDIN_FILENO, EXIT_FAILURE);
	my_dup2(simple(cmd)->outfd, STDOUT_FILENO, EXIT_FAILURE);
	exit(miniexec(simple(cmd)->args));
}

int exec_cmd(t_dlist *cmd)
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
			exit(1);
	}
	pid = fork();
	g_term.lastpid = pid;
	if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		if (pid == 0)
			g_term.lastret = handle_child(cmd);
		else
			g_term.lastret = handle_parent(cmd, pipe_open);
	}
	return (g_term.lastret);
}
