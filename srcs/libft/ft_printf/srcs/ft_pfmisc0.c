#include "../incs/ft_pfmisc0.h"

void	init_opts(t_opts *opts)
{
	opts->signsz = 0;
	opts->baselen = 0;
	opts->nbrlen = 0;
	opts->width = 0;
	opts->precision = 0;
	opts->flags = 0;
	opts->type = '-';
	opts->base = NULL;
	opts->arg.fnbr = 0.0f;
}

int	my_flush(t_printfout *const buffer, t_printfout *const res)
{
	char	*aux;

	if (res->str == NULL)
	{
		aux = ft_calloc(buffer->size + 1, sizeof(*aux));
		if (!aux)
			return (-1);
		ft_memcpy(aux, buffer->str, buffer->size);
	}
	else
	{
		aux = ft_calloc(res->size + 1, sizeof(*aux));
		if (!aux)
			return (-1);
		ft_memcpy(aux, res->str, res->size - buffer->size);
		ft_memcpy(aux + res->size - buffer->size, buffer->str, buffer->size);
		free (res->str);
	}
	res->str = aux;
	ft_bzero(buffer->str, buffer->size + 1);
	buffer->size = 0;
	return (res->size);
}

void	fill_buffer(const char *fmt, t_printfout *const buffer,
					t_printfout *const result)
{
	buffer->str[buffer->size] = *fmt;
	buffer->size++;
	result->size++;
	if (fmt[1] == '\0' || buffer->size == PRINTF_BUFFER_SIZE)
		result->size = my_flush(buffer, result);
}

bool	is_unsigned(char c)
{
	if (c == 'i' || c == 'd')
		return (0);
	return (1);
}
