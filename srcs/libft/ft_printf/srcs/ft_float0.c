#include "../incs/ft_float0.h"

static double	*makepowers(t_uint8 baselen, t_uint8 size, double **ret_orig)
{
	double	*ret_val;
	double	start;
	t_uint8	i;

	if (!na_calloc(sizeof(*ret_val), size + 1, (void **)&ret_val))
		return (NULL);
	*ret_orig = ret_val;
	start = 1.0f;
	i = 0;
	while (i < size)
	{
		ret_val[i++] = start;
		start *= baselen;
	}
	ret_val[i] = 0.0f;
	return (*ret_orig);
}

static void	init_fconfig(t_opts *opts, t_fconfig *conf)
{
	if (!makepowers(opts->baselen, 10, &conf->pow10))
		return ;
	ft_bzero(conf->buf, PRINTF_FTOA_BUFFER_SIZE);
	conf->len = 0U;
	conf->count = 0U;
	conf->negative = 0;
	if (opts->arg.fnbr < 0 && ++conf->negative)
		opts->arg.fnbr *= -1.0f;
	if (!(opts->flags & FLAGS_PRECISION))
		opts->precision = PRINTF_DEFAULT_FLOAT_PRECISION;
	while (opts->precision > 9U)
	{
		conf->buf[conf->len++] = opts->base[0];
		opts->precision--;
		if (conf->len > PRINTF_FTOA_BUFFER_SIZE)
		{
			--conf->len;
			break ;
		}
	}
	conf->whole = (int)opts->arg.fnbr;
	conf->tmp = (opts->arg.fnbr - conf->whole) * conf->pow10[opts->precision];
	conf->frac = (unsigned long)conf->tmp;
	conf->diff = conf->tmp - conf->frac;
}

static void	whole_and_lead_zeroes(t_opts *opts, t_fconfig *conf)
{
	while (conf->len < PRINTF_FTOA_BUFFER_SIZE)
	{
		conf->buf[conf->len++] = opts->base[conf->whole % opts->baselen];
		conf->whole /= opts->baselen;
		if (!conf->whole)
			break ;
	}
	if ((opts->flags & FLAGS_ZEROPAD) != 0)
	{
		if (opts->width && (conf->negative
				|| (opts->flags & (FLAGS_PLUS | FLAGS_SPACE))))
			opts->width--;
		while ((conf->len < opts->width)
			&& (conf->len < PRINTF_FTOA_BUFFER_SIZE))
			conf->buf[conf->len++] = opts->base[0];
	}
}

char	*ft_ftoa(t_opts *opts)
{
	t_fconfig	conf;

	if ((opts->arg.fnbr != opts->arg.fnbr) || (opts->arg.fnbr < -DBL_MAX)
		|| (opts->arg.fnbr > DBL_MAX) || (opts->flags & FLAGS_PLUS)
		|| (opts->arg.fnbr > PTF_MAX_F) || (opts->arg.fnbr < -PTF_MAX_F))
		return (handle_special_floats(opts->arg.fnbr, opts->flags));
	init_fconfig(opts, &conf);
	config_fconf(opts, &conf);
	config_fprec(opts, &conf);
	whole_and_lead_zeroes(opts, &conf);
	if (conf.len < PRINTF_FTOA_BUFFER_SIZE)
	{
		if (conf.negative)
			conf.buf[conf.len++] = '-';
		else if (opts->flags & FLAGS_PLUS)
			conf.buf[conf.len++] = '+';
		else if (opts->flags & FLAGS_SPACE)
			conf.buf[conf.len++] = ' ';
	}
	free (conf.pow10);
	conf.buf[conf.len] = '\0';
	ft_reverse_string(conf.buf);
	return (ft_strdup(conf.buf));
}

char	*place_float(t_opts *opts, char *content, char **field)
{
	if (opts->width < ft_strlen(content))
		opts->width = ft_strlen(content);
	if (!na_calloc (opts->width + 1, 1, (void **)field))
		return (NULL);
	ft_memset(*field, ' ', opts->width);
	if ((opts->flags & FLAGS_LEFT) == 0 )
		align_right(*field, content);
	else
		ft_wrtptr(*field, content);
	return (*field);
}
