#include "../incs/ft_outprintf.h"

static void	set_flags(t_opts *opts, const char **fmt)
{
	if (**fmt == '-')
	{
		opts->flags &= ~FLAGS_ZEROPAD;
		opts->flags |= FLAGS_LEFT;
		(*fmt)++;
	}
	else if (**fmt == '0')
	{
		if (!(opts->flags & FLAGS_LEFT))
			opts->flags |= FLAGS_ZEROPAD;
		(*fmt)++;
	}
	else if (**fmt == ' ')
	{
		opts->flags |= FLAGS_SPACE;
		(*fmt)++;
	}
	else
	{
		opts->flags |= FLAGS_PLUS;
		(*fmt)++;
	}
}

static void	retrieve_int_arg(t_opts *opts, const char **fmt, size_t *param,
			va_list ap)
{
	int			arg;

	if (ft_isdigit(**fmt))
		*param = ft_atoi_adv((char **)fmt);
	else
	{
		arg = va_arg(ap, long int);
		if (arg < 0)
		{
			*param = -(arg);
			if (param == &opts->width)
				opts->flags |= FLAGS_LEFT;
			else
			{
				opts->precision = 0;
				opts->flags &= ~FLAGS_PRECISION;
			}
		}
		else
			*param = (size_t)arg;
		(*fmt)++;
	}
}

static void	get_opts(t_opts *opts, const char **fmt, va_list ap)
{
	while (**fmt == '-' || **fmt == '0' || **fmt == ' ' || **fmt == '+')
		set_flags(opts, fmt);
	if (ft_isdigit(**fmt) || **fmt == '*')
	{
		opts->flags |= FLAGS_WIDTH;
		retrieve_int_arg(opts, fmt, &opts->width, ap);
	}
	if (**fmt == '.')
	{
		(*fmt)++;
		opts->flags &= ~FLAGS_ZEROPAD;
		opts->flags |= FLAGS_PRECISION;
		if (ft_isdigit(**fmt) || **fmt == '*')
			retrieve_int_arg(opts, fmt, &opts->precision, ap);
	}
}

static void	handle_args(t_printfout *const output, t_printfout *const buffer,
			const char **fmt, va_list ap)
{
	t_opts	opts;

	init_opts(&opts);
	(*fmt)++;
	get_opts(&opts, fmt, ap);
	if (**fmt == 'c' || **fmt == '%')
	{
		if (**fmt == '%')
			opts.arg.chr = '%';
		get_char(output, buffer, &opts, ap);
		return ;
	}
	if (**fmt == 's' || **fmt == 'p')
	{
		opts.type = **fmt;
		get_pointer(output, buffer, &opts, ap);
		return ;
	}
	if (**fmt == 'd' || **fmt == 'i' || **fmt == 'x' || **fmt == 'X'
		|| **fmt == 'u' || **fmt == 'o' || **fmt == 'b' || **fmt == 'f')
	{
		opts.type = **fmt;
		get_number(output, buffer, &opts, ap);
		return ;
	}
}

void	ft_outprintf(t_printfout *const output, const char *format, va_list ap)
{
	t_printfout	buffer;

	buffer.size = 0;
	if (!na_calloc(PRINTF_BUFFER_SIZE + 1, sizeof(char), (void **)&buffer.str))
	{
		output->size = -1;
		return ;
	}
	while (*format)
	{
		if (*format != '%')
			fill_buffer(format, &buffer, output);
		else
			handle_args(output, &buffer, &format, ap);
		if (*format)
			format++;
		if (output->size < 0)
			break ;
	}
	if (buffer.size > 0 && output->size > -1 )
		my_flush(&buffer, output);
	free(buffer.str);
}
