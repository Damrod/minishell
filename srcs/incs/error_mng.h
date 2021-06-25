#ifndef ERROR_MNG_H
# define ERROR_MNG_H

# include <libft.h>
# include <minishell0.h>
# include <stdint.h>

void	free_and_nullify(void **tofree);
void	handle_eot(int sig);
int		error_syntax(char *token, int *prunepattern);
int		warning_shell(char *token, uint32_t line);
int		error_file(char *file, int *prunepattern);

#endif
