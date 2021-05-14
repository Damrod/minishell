#include "../incs/ft_nitoa_helpers.h"

static void	nbrlen_unsigned(t_opts *opts)
{
	unsigned int		unbr;
	unsigned long int	lnbr;

	if (opts->type != 'p')
	{
		unbr = opts->arg.unbr;
		while (1)
		{
			unbr /= opts->baselen;
			opts->nbrlen++;
			if (unbr == 0)
				break ;
		}
		return ;
	}
	lnbr = opts->arg.lnbr;
	while (1)
	{
		lnbr /= opts->baselen;
		opts->nbrlen++;
		if (lnbr == 0)
			break ;
	}
	return ;
}

void	nbrlen(t_opts *opts)
{
	int					nbr;

	if (is_unsigned(opts->type))
		return (nbrlen_unsigned(opts));
	if (opts->arg.nbr < 0 || (opts->flags & FLAGS_SPACE)
		|| (opts->flags & FLAGS_PLUS))
	{
		++opts->signsz;
		opts->nbrlen = 1;
	}
	nbr = opts->arg.nbr;
	while (1)
	{
		nbr /= opts->baselen;
		opts->nbrlen++;
		if (nbr == 0)
			break ;
	}
}

void	handle_overflow(char *negative, char **result, t_opts *opts,
			t_uint8 *size)
{
	*negative = 1;
	(*result)[*size - 1] = opts->base[-(opts->arg.nbr % opts->baselen)];
	opts->arg.nbr = -(opts->arg.nbr / (int)opts->baselen);
	(*result)++;
	(*size) -= 2;
}

void	handle_negative(char *negative, char **result, int *nbr, t_uint8 *size)
{
	*negative = 1;
	(*nbr) *= -1;
	(*result)++;
	(*size)--;
}

void	get_digit_loop(t_opts *opts, char *result)
{
	if (!is_unsigned(opts->type))
	{
		result[opts->nbrlen - 1] = opts->base[opts->arg.nbr % opts->baselen];
		opts->arg.nbr /= opts->baselen;
	}
	else
	{
		if (opts->type != 'p')
		{
			result[opts->nbrlen - 1]
				= opts->base[opts->arg.unbr % opts->baselen];
			opts->arg.unbr /= opts->baselen;
		}
		else
		{
			result[opts->nbrlen - 1]
				= opts->base[opts->arg.lnbr % (size_t)opts->baselen];
			opts->arg.lnbr /= (size_t)opts->baselen;
		}
	}
	opts->nbrlen--;
}
