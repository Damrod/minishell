#ifndef FT_VPRINTF_H
# define FT_VPRINTF_H

# include "../../libft.h"
# include "ft_outprintf.h"

int	ft_vprintf(const char *format, va_list ap);
int	ft_vdprintf(int fd, const char *format, va_list ap);
int	ft_vsprintf(char *str, const char *format, va_list ap);
int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap);

#endif
