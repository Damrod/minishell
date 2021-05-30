#include <libft.h>

void	ft_dlstpush_front(t_dlist **lst, void *content)
{
	t_dlist	*aux;

	na_dlstnew(content, &aux);
	if (!aux)
		return ;
	ft_dlstadd_front(lst, aux);
}
