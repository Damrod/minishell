#ifndef FT_GETTYPE_H
# define FT_GETTYPE_H

# include "ft_printf_private.h"
# include "ft_pfmisc0.h"
# include "ft_gettype1.h"
# include "ft_float0.h"

void	get_number(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts, va_list ap);
ssize_t	get_char(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts, va_list ap);
ssize_t	get_pointer(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts, va_list ap);

#endif
