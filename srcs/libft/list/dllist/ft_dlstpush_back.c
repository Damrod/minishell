#include <libft.h>

void	ft_dlstpush_back(t_dlist **lst, void *content)
{
	t_dlist	*aux;

	na_dlstnew(content, &aux);
	if (!aux)
		return ;
	ft_dlstadd_back(lst, aux);
}
