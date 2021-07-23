#ifndef MINISHELL0_H
# define MINISHELL0_H

# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
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

typedef struct s_term {
	char		**path;
	char		**environ;
	uint32_t	lineno;
	uint8_t		lastret;
}	t_term;

t_list			*get_args(const char *arg);
size_t			ft_wstrlen(const unsigned short *str, char is_untilspace);
unsigned short	*upcast_str(const char *args);
unsigned short	*ft_wstrdup(const unsigned short *str, char is_untilspace);
void			print_dblptr(const char *input);
void			apply_dblptr(char **data, void (*f)());
char			**ft_dblptr_cpy(const char **data,
					const char *item, char is_deep);
t_dlist			*build_cmd_table(t_dlist **simplecmds);
void			*comp_dtor(t_dlist **compcmd, t_dlist *simplecmds,
					bool isprintsynerr);
int				exec_cmd(t_dlist *cmd);
int				get_pipes(void *src, void *key);

extern t_term	g_term;

#endif
