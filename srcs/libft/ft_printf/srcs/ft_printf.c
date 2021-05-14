#include "../incs/ft_printf_private.h"

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			ret_val;

	va_start(ap, format);
	ret_val = ft_vprintf(format, ap);
	va_end(ap);
	return (ret_val);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list		ap;
	int			ret_val;

	va_start(ap, format);
	ret_val = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret_val);
}

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list		ap;
	int			ret_val;

	va_start(ap, format);
	ret_val = ft_vsprintf(str, format, ap);
	va_end(ap);
	return (ret_val);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list		ap;
	int			ret_val;

	va_start(ap, format);
	ret_val = ft_vsnprintf(str, size, format, ap);
	va_end(ap);
	return (ret_val);
}
