#include "../incs/ft_formattypes.h"

int	ft_nitoa(t_opts *opts, char **content)
{
	char	*result;
	char	positive;
	char	negative;

	if (!na_calloc (sizeof(*result), (opts->nbrlen + 1), (void **)&result))
		return (0);
	*content = result;
	negative = 0;
	positive = 0;
	if (!is_unsigned(opts->type) && (opts->arg.nbr >= 0)
		&& ((opts->flags & FLAGS_SPACE) || (opts->flags & FLAGS_PLUS)))
		positive = 1;
	if (!is_unsigned(opts->type) && opts->arg.nbr == -2147483648)
		handle_overflow(&negative, &result, opts, &opts->nbrlen);
	if (!is_unsigned(opts->type) && opts->arg.nbr < 0)
		handle_negative(&negative, &result, &opts->arg.nbr, &opts->nbrlen);
	while (opts->nbrlen)
		get_digit_loop(opts, result);
	if (negative)
		**content = '-';
	if (positive && (opts->flags & FLAGS_SPACE))
		**content = ' ';
	if (positive && (opts->flags & FLAGS_PLUS))
		**content = '+';
	return (1);
}

static char	*configure_opts_and_field(t_opts *opts, char **field)
{
	if (opts->type == 'i' || opts->type == 'd' || opts->type == 'u'
		|| opts->type == 'x' || opts->type == 'X' || opts->type == 'b'
		|| opts->type == 'o' || opts->type == 'p')
	{
		if (opts->precision < (unsigned)(opts->nbrlen - opts->signsz))
			opts->precision = opts->nbrlen - opts->signsz;
		if (opts->width < opts->precision + opts->signsz
			|| (opts->flags & FLAGS_WIDTH) == 0)
			opts->width = opts->precision + opts->signsz;
		opts->nbrlen = opts->precision + opts->signsz;
	}
	if (!na_calloc (opts->width + 1, 1, (void **)field))
		return (NULL);
	if (opts->flags & FLAGS_LEFT)
		opts->flags &= ~FLAGS_ZEROPAD;
	if ((opts->flags & FLAGS_ZEROPAD) != 0)
		opts->nbrlen = opts->width;
	ft_memset(*field, ' ', opts->width);
	return (*field);
}

char	*format_str(char *str, t_opts *opts)
{
	char	*field;

	if (!(opts->flags & FLAGS_WIDTH) || opts->width < ft_strlen(str))
		opts->width = ft_strlen(str);
	field = ft_calloc (opts->width + 1, 1);
	if (!field)
		return (NULL);
	ft_memset(field, ' ', opts->width);
	if ((opts->flags & FLAGS_LEFT) == 0)
		align_right(field, str);
	else
		ft_wrtptr(field, str);
	return (field);
}

char	*format_nbr(t_opts *opts)
{
	char	*field;
	char	*content;

	content = NULL;
	if (opts->arg.nbr == 0 && opts->precision == 0
		&& (opts->flags & FLAGS_PRECISION))
	{
		if (!na_alloc((void *)ft_strdup, e_ptr, "", (void **)&content))
			return (NULL);
		if (!(opts->flags & FLAGS_WIDTH))
			return (content);
	}
	if (!configure_opts_and_field(opts, &field))
		return (NULL);
	if (!content && !ft_nitoa(opts, &content))
	{
		free (field);
		return (NULL);
	}
	if ((opts->flags & FLAGS_LEFT) == 0 )
		align_right(field, content);
	else
		ft_wrtptr(field, content);
	free(content);
	return (field);
}
