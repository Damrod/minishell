#include <libft.h>

#define EXIT_FAILED 1
#define SIDE_OUT	0
#define SIDE_IN		1

#define TYPE_END		0
#define TYPE_PIPE		1
#define TYPE_BREAK		2
#define TYPE_GREAT		3
#define TYPE_GREATGREAT	4
#define TYPE_LESS		5

#ifdef TEST_SH
# define TEST			1
#else
# define TEST			0
#endif

typedef struct s_simplecmd
{
	char				**args;
	int					length;
	int					type;
	int					pipes[2];
}						t_simplecmd;

typedef struct s_cmpcmd
{
	t_dlist				list;
	char				**args;
	int					length;
	int					type;
	int					pipes[2];
}						t_cmpcmd;

#include <stdbool.h>
#include <sys/wait.h>

char *resolve_cmd_path(char *cmd);

t_simplecmd	*simple(t_dlist *comp_cmds)
{
	if (!comp_cmds)
		return NULL;
	return ((t_simplecmd*)comp_cmds->content);
}

/* int	exec_cmd(t_dlist *comp_cmds, char **environ) */
/* { */
/* 	int pid; */
/* 	bool openpipe; */
/* 	int status; */
/* 	int ret; */

/* 	ret = EXIT_FAILED; */
/* 	openpipe = 0; */
/* 	if(simple(comp_cmds)->type == TYPE_PIPE || (simple(comp_cmds->prev) && simple(comp_cmds->prev)->type == TYPE_PIPE)) */
/* 	{ */
/* 		openpipe = 1; */
/* 		pipe(simple(comp_cmds)->pipes); */
/* 	} */
/* 	pid = fork(); */
/* 	if (pid == 0) */
/* 	{ */
/* 		if(simple(comp_cmds)->type == TYPE_PIPE) */
/* 			dup2(simple(comp_cmds)->pipes[1], STDOUT_FILENO); */
/* 		if(simple(comp_cmds->prev) && simple(comp_cmds->prev)->type == TYPE_PIPE) */
/* 			dup2(simple(comp_cmds)->pipes[0], STDIN_FILENO); */
/* 		execve(resolve_cmd_path(simple(comp_cmds)->args[0]), simple(comp_cmds)->args, environ); */
/* 	} */
/* 	else */
/* 	{ */
/* 		waitpid(pid, &status, 0); */
/* 		if (openpipe && simple(comp_cmds)->type == TYPE_PIPE) */
/* 			close(simple(comp_cmds)->pipes[1]); */
/* 		if (WIFEXITED(status)) */
/* 			ret = WEXITSTATUS(status); */
/* 	} */
/* 	return ret; */
/* } */
