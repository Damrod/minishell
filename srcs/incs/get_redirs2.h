#ifndef GET_REDIRS2_H
# define GET_REDIRS2_H

# include <libft.h>
# include <stdbool.h>

int	to_input(int *input, char *file, bool is_last);
int	to_append(int *output, char *file, bool is_last);
int	to_output(int *output, char *file, bool is_last);
int	to_heredoc(int *input, char *file, bool is_last);
int	get_io_file(char **file, unsigned short *listcont, bool *islast);

#endif
