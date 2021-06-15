#ifndef MINISHELL0_H
# define MINISHELL0_H

# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define FLAG_ESCAPED (0b0100000000000000)
# define FLAG_SNGQUOT (0b0010000000000000)
# define FLAG_DBLQUOT (0b0001000000000000)
# define FLAG_NOTSPCE (0b0000100000000000)
# define FLAG_CIGNORE (0b0000010000000000)

# define UNTIL_END_OF_STRING 0
# define UNTIL_NON_QUOTED_SPACE 1
# define UNTIL_ANY_SPACE 2

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

typedef struct s_term {
	char	*inputstring;
}	t_term;

unsigned short	**get_args(const char *arg);
size_t			ft_wstrlen(const unsigned short *str, char is_untilspace);

extern t_term	g_term;

#endif
