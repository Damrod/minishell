#ifndef GET_REDIRS2_H
# define GET_REDIRS2_H

# include <stdbool.h>
# include <wstrcmp.h>
# include <get_tokens.h>
# include <heredoc.h>

int	to_input(int *input, char *file, bool is_last);
int	to_append(int *output, char *file, bool is_last);
int	to_output(int *output, char *file, bool is_last);
int	to_heredoc(int *input, char *file, bool is_last, uint32_t *lineno);
int	get_io_file(char **file, unsigned short *listcont, bool *islast);

#endif
