#ifndef FT_FLOAT1_H
# define FT_FLOAT1_H

# include "ft_printf_private.h"

char	*handle_special_floats(double nbr, t_uint8 flags);
void	config_fconf(t_opts *opts, t_fconfig *conf);
void	config_fprec(t_opts *opts, t_fconfig *conf);

#endif
