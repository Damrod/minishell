#include "../incs/ft_gettype1.h"

char	*get_base(char type, ssize_t *error)
{
	char	*base;
	char	*ret_val;

	if (type == 'i' || type == 'd' || type == 'u' || type == 'f')
		base = "0123456789";
	if (type == 'x' || type == 'p')
		base = "0123456789abcdef";
	if (type == 'X')
		base = "0123456789ABCDEF";
	if (type == 'o')
		base = "01234567";
	if (type == 'b')
		base = "01";
	ret_val = ft_strdup(base);
	if (!ret_val)
		*error = -1;
	return (ret_val);
}

void	get_number2(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts, va_list ap)
{
	char	*aux;
	size_t	i;

	if (!is_unsigned(opts->type))
		opts->arg.nbr = va_arg(ap, int);
	else
		opts->arg.unbr = va_arg(ap, unsigned int);
	nbrlen(opts);
	aux = format_nbr(opts);
	if (!aux)
	{
		free (opts->base);
		output->size = -1;
		return ;
	}
	i = 0;
	while (aux[i] != '\0')
		fill_buffer(&aux[i++], buffer, output);
	free (aux);
	free (opts->base);
}

ssize_t	get_string(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts)
{
	char	*aux;
	char	*str_heap;
	size_t	i;

	if (opts->arg.ptr == NULL)
		opts->arg.ptr = "(null)";
	if (!na_alloc((void *)ft_strdup, e_ptr, opts->arg.ptr, (void **)&str_heap))
		return (output->size = -1);
	if ((opts->flags & FLAGS_PRECISION)
		&& opts->precision < ft_strlen(str_heap))
		str_heap[opts->precision] = '\0';
	aux = format_str(str_heap, opts);
	if (!aux)
	{
		free(str_heap);
		free (output->str);
		return (output->size = -1);
	}
	i = 0;
	while (aux[i] != '\0')
		fill_buffer(&aux[i++], buffer, output);
	free(str_heap);
	free(aux);
	return (output->size);
}

static void	fill_buf_add_pref_ptr_str(t_printfout *const output,
			t_printfout *const buffer, char *str, const char *prefix)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && j < 2)
			fill_buffer(&prefix[j++], buffer, output);
		else
		{
			if (k < 2 && str[i] == ' ')
			{
				i++;
				k++;
				continue ;
			}
			fill_buffer(&str[i++], buffer, output);
		}
	}
}

ssize_t	get_void_pointer(t_printfout *const output, t_printfout *const buffer,
			t_opts *opts)
{
	static const char	*prefix = "0x";
	char				*str;

	opts->base = get_base(opts->type, &output->size);
	opts->baselen = ft_strlen(opts->base);
	if (output->size < 0)
		return (-1);
	nbrlen(opts);
	str = format_nbr(opts);
	if (!str)
	{
		free (output->str);
		return (output->size = -1);
	}
	fill_buf_add_pref_ptr_str(output, buffer, str, prefix);
	free (str);
	free (opts->base);
	return (output->size);
}
