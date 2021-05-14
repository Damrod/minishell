#include "../incs/ft_gettype.h"

static void	get_float(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts, va_list ap)
{
	char	*aux;
	char	*field;
	size_t	i;

	opts->arg.fnbr = va_arg(ap, double);
	aux = ft_ftoa(opts);
	if (!aux)
	{
		free (opts->base);
		output->size = -1;
		return ;
	}
	if (!place_float(opts, aux, &field))
	{
		free (opts->base);
		free (aux);
		output->size = -1;
		return ;
	}
	free (aux);
	i = 0;
	while (field[i] != '\0')
		fill_buffer(&field[i++], buffer, output);
	free (field);
	free (opts->base);
}

void	get_number(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts, va_list ap)
{
	opts->base = get_base(opts->type, &output->size);
	if (output->size < 0)
		return ;
	opts->baselen = ft_strlen(opts->base);
	if (opts->type == 'x' || opts->type == 'X' || opts->type == 'u'
		|| opts->type == 'b' || opts->type == 'o' || opts->type == 'd'
		|| opts->type == 'i')
	{
		get_number2(output, buffer, opts, ap);
		return ;
	}
	if (opts->type == 'f')
		get_float(output, buffer, opts, ap);
	return ;
}

ssize_t	get_char(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts, va_list ap)
{
	const char			*tmp;
	static const char	*zero = "00";
	static const char	*space = "  ";
	size_t				charpos;

	if (opts->arg.chr != '%')
		opts->arg.chr = (char)va_arg(ap, int);
	if (!(opts->flags & FLAGS_WIDTH))
		opts->width = 1U;
	charpos = 0;
	if (opts->flags & FLAGS_LEFT)
		charpos = opts->width - 1U;
	tmp = space;
	if (opts->flags & FLAGS_ZEROPAD)
		tmp = zero;
	while (opts->width)
	{
		if ((opts->width - 1) == charpos)
			fill_buffer(&opts->arg.chr, buffer, output);
		else
			fill_buffer(tmp, buffer, output);
		--opts->width;
	}
	return (output->size);
}

ssize_t	get_pointer(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts, va_list ap)
{
	opts->arg.ptr = va_arg(ap, void *);
	if (opts->type == 's')
		get_string(output, buffer, opts);
	else
		get_void_pointer(output, buffer, opts);
	return (output->size);
}
