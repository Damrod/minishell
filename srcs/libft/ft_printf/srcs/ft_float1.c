#include "../incs/ft_float1.h"

char	*handle_special_floats(double nbr, t_uint8 flags)
{
	if (nbr != nbr)
		return (ft_strdup("nan"));
	if (nbr < -DBL_MAX)
		return (ft_strdup("-inf"));
	if (nbr > DBL_MAX)
	{
		if (flags & FLAGS_PLUS)
			return (ft_strdup("+inf"));
		else
			return (ft_strdup("inf"));
	}
	if ((nbr > PTF_MAX_F) || (nbr < -PTF_MAX_F))
		return (NULL);
	return (NULL);
}

void	config_fconf(t_opts *opts, t_fconfig *conf)
{
	if (conf->diff > 0.5)
	{
		++conf->frac;
		if (conf->frac >= conf->pow10[opts->precision])
		{
			conf->frac = 0;
			++conf->whole;
		}
	}
	else if (conf->diff < 0.5)
		;
	else if ((conf->frac == 0U) || (conf->frac & 1U))
		++conf->frac;
}

void	config_fprec(t_opts *opts, t_fconfig *conf)
{
	if (opts->precision == 0U)
	{
		conf->diff = opts->arg.fnbr - (double)conf->whole;
		if ((!(conf->diff < 0.5) || (conf->diff > 0.5)) && (conf->whole & 1))
			++conf->whole;
	}
	else
	{
		conf->count = opts->precision;
		while (conf->len < PRINTF_FTOA_BUFFER_SIZE)
		{
			--conf->count;
			conf->buf[conf->len++] = opts->base[conf->frac % opts->baselen];
			conf->frac /= opts->baselen;
			if (!conf->frac)
				break ;
		}
		while ((conf->len < PRINTF_FTOA_BUFFER_SIZE) && (conf->count-- > 0U))
			conf->buf[conf->len++] = opts->base[0];
		if (conf->len < PRINTF_FTOA_BUFFER_SIZE)
			conf->buf[conf->len++] = '.';
	}
}
