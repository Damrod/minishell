#ifndef FT_GETTYPE1_H
# define FT_GETTYPE1_H

# include "ft_printf_private.h"
# include "ft_pfmisc0.h"
# include "ft_formattypes.h"

char	*get_base(char type, ssize_t *error);
void	get_number2(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts, va_list ap);
ssize_t	get_string(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts);
ssize_t	get_void_pointer(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts);

#endif
