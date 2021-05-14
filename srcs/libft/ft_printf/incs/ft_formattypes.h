#ifndef FT_FORMATTYPES_H
# define FT_FORMATTYPES_H
# include "ft_printf_private.h"
# include "ft_nitoa_helpers.h"
# include "ft_pfmisc0.h"

int		ft_nitoa(t_opts *opts, char **content);
char	*format_str(char *str, t_opts *opts);
char	*format_nbr(t_opts *opts);

#endif
