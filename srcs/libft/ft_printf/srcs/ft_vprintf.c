#include "../incs/ft_vprintf.h"

int	ft_vprintf(const char *format, va_list ap)
{
	t_printfout	output;
	char		*fmt;
	ssize_t		ret_val;

	output.str = NULL;
	output.size = 0;
	fmt = ft_strdup(format);
	if (!fmt)
		return (-1);
	ft_outprintf(&output, fmt, ap);
	free(fmt);
	if (output.size > -1)
		ret_val = write(1, output.str, output.size);
	else
	{
		free (output.str);
		return (-1);
	}
	free (output.str);
	return (ret_val);
}

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_printfout	output;
	char		*fmt;
	ssize_t		ret_val;

	output.str = NULL;
	output.size = 0;
	fmt = ft_strdup(format);
	if (!fmt)
		return (-1);
	ft_outprintf(&output, fmt, ap);
	free(fmt);
	if (output.size > -1)
		ret_val = write(fd, output.str, output.size);
	else
	{
		free (output.str);
		return (-1);
	}
	free (output.str);
	return (ret_val);
}

int	ft_vsprintf(char *str, const char *format, va_list ap)
{
	t_printfout	output;
	char		*fmt;

	output.str = NULL;
	output.size = 0;
	fmt = ft_strdup(format);
	if (!fmt)
		return (-1);
	ft_outprintf(&output, format, ap);
	free(fmt);
	if (output.size > -1)
	{
		ft_memcpy(str, output.str, output.size);
		str[output.size] = '\0';
	}
	free (output.str);
	return (output.size);
}

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	t_printfout	output;
	char		*fmt;

	output.str = NULL;
	output.size = 0;
	fmt = ft_strdup(format);
	if (!fmt)
		return (-1);
	ft_outprintf(&output, format, ap);
	free(fmt);
	if ((int)size < output.size)
		output.size = size;
	if (output.size > -1)
	{
		ft_memcpy(str, output.str, output.size);
		str[output.size] = '\0';
	}
	free (output.str);
	return (output.size);
}
