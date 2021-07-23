#ifndef ERROR_MNG_H
# define ERROR_MNG_H

# include <minishell.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

int		free_and_nullify(void **tofree0, void **tofree1, void **tofree2,
			int retvalue);
void	handle_noop(int sig);
void	handle_int(int sig);
int		error_syntax(char *token);
int		warning_shell(char *token, uint32_t line);
int		error_file(char *file);
int		error_cmd(char *builtin, char *arg, char *msg, int nbr);
int		error_custom(void **freeme0, void **freeme1, void **freeme2, char *msg);
int		selfassignment(int *retnbr, int nbr, int retval);
void	*clean_ptr(void **tofre0, void **tofre1, void **tofre2, void *retval);

#endif
