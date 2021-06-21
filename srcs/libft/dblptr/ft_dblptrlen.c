#include <stdlib.h>

size_t	ft_dblptrlen(void **data)
{
	size_t	len;

	len = 0;
	if (data)
	{
		while (data[len])
			len++;
	}
	return (len);
}
