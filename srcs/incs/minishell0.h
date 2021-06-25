#ifndef MINISHELL0_H
# define MINISHELL0_H

# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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

# define NUL 0x00
# define SOH 0x01
# define STX 0x02
# define ETX 0x03
# define EOT 0x04
# define ENQ 0x05
# define ACK 0x06
# define BEL 0x07
# define BS 0x08
# define HT 0x09
# define LF 0x0A
# define VT 0x0B
# define FF 0x0C
# define CR 0x0D
# define SO 0x0E
# define SI 0x0F
# define DLE 0x10
# define DC1 0x11
# define DC2 0x12
# define DC3 0x13
# define DC4 0x14
# define NAK 0x15
# define SYN 0x16
# define ETB 0x17
# define CAN 0x18
# define EM 0x19
# define SUB 0x1A
# define FS 0x1C
# define GS 0x1D
# define RS 0x1E
# define US 0x1F
# define DEL 0x7F

typedef struct s_compcmd {
	char			**args;
	char			type;
	int				pipes[2];
}	t_compcmd;

typedef struct s_term {
	char		**args;
	char		**environ;
	char		*inputstring;
	t_dlist		*cmds;
	int			infd;
	int			outfd;
	uint8_t		lastret;
	uint32_t	lineno;
}	t_term;

t_list	*get_args(const char *arg);
size_t			ft_wstrlen(const unsigned short *str, char is_untilspace);
unsigned short	*upcast_str(const char *args);
unsigned short	*ft_wstrdup(const unsigned short *str, char is_untilspace);

extern t_term	g_term;

#endif
