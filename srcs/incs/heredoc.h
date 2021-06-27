#ifndef HEREDOC_H
# define HEREDOC_H

# include <stdbool.h>
# include <sys/stat.h>
# include <error_mng.h>
# include <minishell0.h>

int	heredoc_get_fd(char *result, int *input, char *file);
int	heredoc_getline(char *file, char **result);

#endif
