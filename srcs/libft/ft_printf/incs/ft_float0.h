#ifndef FT_FLOAT0_H
# define FT_FLOAT0_H

# include "ft_printf_private.h"
# include "ft_float1.h"

char	*ft_ftoa(t_opts *opts);
char	*place_float(t_opts *opts, char *content, char **field);
char	*ft_ftoa(t_opts *opts);

#endif
