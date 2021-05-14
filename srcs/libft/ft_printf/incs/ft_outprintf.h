#ifndef FT_OUTPRINTF_H
# define FT_OUTPRINTF_H
# include "ft_printf_private.h"
# include "../../libft.h"
# include "ft_pfmisc0.h"
# include "ft_gettype.h"

void		ft_outprintf(t_printfout *const output, const char *format,
				va_list ap);
#endif
