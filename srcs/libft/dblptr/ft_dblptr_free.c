#include <stdlib.h>

void	*ft_dblptr_free(void **ptrs)
{
	void	**orig;

	orig = ptrs;
	while (*ptrs)
	{
		free (*ptrs);
		ptrs++;
	}
	free(orig);
	return (NULL);
}
