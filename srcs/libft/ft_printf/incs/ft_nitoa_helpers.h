#ifndef FT_NITOA_HELPERS_H
# define FT_NITOA_HELPERS_H

# include "ft_printf_private.h"
# include "ft_pfmisc0.h"

void	nbrlen(t_opts *opts);
void	handle_overflow(char *negative, char **result, t_opts *opts,
			t_uint8 *size);
void	handle_negative(char *negative, char **result, int *nbr, t_uint8 *size);
void	get_digit_loop(t_opts *opts, char *result);

#endif
