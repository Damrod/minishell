#include <libft.h>

void	*na_malloc(size_t size, void **ret_val)
{
	if (!ret_val)
		return (NULL);
	*ret_val = malloc(size);
	return (*ret_val);
}

void	*na_calloc(size_t nmemb, size_t size, void **ret_val)
{
	if (!ret_val)
		return (NULL);
	*ret_val = ft_calloc(nmemb, size);
	return (*ret_val);
}

void	*na_alloc(void *(*allocf)(), enum e_types type, void *param,
			void **ret_val)
{
	size_t	size;

	if (!ret_val)
		return (NULL);
	if (type == e_ptr)
		*ret_val = allocf(param);
	if (type == e_luint)
	{
		size = *(size_t *)param;
		*ret_val = allocf(size);
	}
	return (*ret_val);
}
