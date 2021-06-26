#ifndef GET_REDIRS_H
# define GET_REDIRS_H

# include <libft.h>
# include <stdbool.h>

int	to_input(int *input, char *file, int *prunepattern, bool is_last);
int	to_append(int *output, char *file, int *prunepattern, bool is_last);
int	to_output(int *output, char *file, int *prunepattern, bool is_last);
int	to_heredoc(int *input, char *file, int *prunepattern, bool is_last);
int	get_io_file(char **file, unsigned short *listcont,
		bool *islast, int *prunepattern);
int	get_redirs(t_list **args, int *input, int *output);

#endif
