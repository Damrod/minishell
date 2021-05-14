#ifndef FT_PFMISC0_H
# define FT_PFMISC0_H
# include "ft_printf_private.h"

void	init_opts(t_opts *opts);
int		my_flush(t_printfout *const buffer, t_printfout *const res);
void	fill_buffer(const char *fmt, t_printfout *const buffer,
			t_printfout *const result);
bool	is_unsigned(char c);

#endif
