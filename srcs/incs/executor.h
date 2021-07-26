#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <minishell.h>
# include <sys/wait.h>
# include <env.h>
# include <misc.h>
# include <wstrcmp.h>
# include <get_redirs.h>
# include <error_mng.h>

enum e_pipesides {
	SIDE_OUT = 0,
	SIDE_IN = 1
};

int			exec_cmd(t_dlist *cmd);
int			check_builtins(char **args, char ***env, int *ret);
t_simplcmd	*simple(t_dlist *cmd);
void		*comp_dtor(t_dlist **compcmd, t_dlist *simplecmds,
				bool isprintsynerr);
t_dlist		*build_cmd_table(t_dlist **simplecmds, uint32_t *lineno);

#endif
