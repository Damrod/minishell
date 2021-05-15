#ifndef FT_PRINTF_PRIVATE_H
# define FT_PRINTF_PRIVATE_H

# include <stdarg.h>
# include <stdbool.h>
# include <limits.h>
# include <float.h>
# include <libft.h>

# define FLAGS_ZEROPAD		0b00000001
# define FLAGS_LEFT			0b00000010
# define FLAGS_PRECISION	0b00000100
# define FLAGS_WIDTH		0b00001000
# define FLAGS_PLUS			0b00010000
# define FLAGS_SPACE		0b00100000
# define FLAGS_PERCENT		0b01000000

# ifndef PRINTF_BUFFER_SIZE
#  define PRINTF_BUFFER_SIZE 2048
# endif
# ifndef PRINTF_DEFAULT_FLOAT_PRECISION
#  define PRINTF_DEFAULT_FLOAT_PRECISION  6U
# endif
# ifndef PRINTF_FTOA_BUFFER_SIZE
#  define PRINTF_FTOA_BUFFER_SIZE 2000
# endif
# ifndef PTF_MAX_F
#  define PTF_MAX_F 1e9
# endif

typedef unsigned char	t_uint8;
typedef signed char		t_int8;

typedef struct s_printfout {
	ssize_t			size;
	char			*str;
}				t_printfout;

union u_type {
	void			*ptr;
	double			fnbr;
	size_t			lnbr;
	int				nbr;
	unsigned int	unbr;
	char			chr;
};

typedef struct s_opts {
	union u_type	arg;
	char			*base;
	size_t			width;
	size_t			precision;
	t_uint8			baselen;
	t_uint8			flags;
	t_uint8			nbrlen;
	t_uint8			signsz;
	char			type;
}				t_opts;

typedef struct s_fconfig {
	char			buf[PRINTF_FTOA_BUFFER_SIZE];
	double			*pow10;
	double			diff;
	double			tmp;
	size_t			len;
	size_t			frac;
	size_t			count;
	int				whole;
	t_uint8			negative;
}				t_fconfig;

int	ft_vprintf(const char *format, va_list ap);
int	ft_vdprintf(int fd, const char *format, va_list ap);
int	ft_vsprintf(char *str, const char *format, va_list ap);
int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap);

#endif
