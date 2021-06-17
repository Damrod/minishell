#include <stdlib.h>

void	*freedblptr(void **ptrs)
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
