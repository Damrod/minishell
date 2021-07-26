#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdbool.h>

# define EXENAME "minishell"

# define FLAG_ESCAPED (0b0100000000000000)
# define FLAG_SNGQUOT (0b0010000000000000)
# define FLAG_DBLQUOT (0b0001000000000000)
# define FLAG_NOTSPCE (0b0000100000000000)
# define FLAG_CIGNORE (0b0000010000000000)

# define UNTIL_END_OF_STRING 0
# define UNTIL_NON_QUOTED_SPACE 1
# define UNTIL_ANY_SPACE 2
# define UNTIL_ANY_ENDOFTOKEN 3

# define CHECK_ONLY_LOW 0
# define CHECK_SNGQUOTE 1
# define CHECK_DBLQUOTE 2
# define CHECK_ANYQUOTE 3
# define CHECK_NOTQUOTE 4

enum e_type {
	TYPE_NO = -1,
	TYPE_OUT = 0,
	TYPE_IN	 = 1,
	TYPE_APP = 2,
	TYPE_HEREDOC = 3,
	TYPE_END = 4,
	TYPE_PIPE = 5,
};

typedef struct s_compcmd {
	char			**args;
	char			type;
	int				pipes[2];
	int				outfd;
	int				infd;
}	t_simplcmd;

t_list			*get_args(const char *arg, char **env);

extern uint8_t		g_lastret;

#endif
