#include <libft.h>

t_dlist	*ft_dlstpop_back(t_dlist **lst)
{
	t_dlist	*aux1;
	t_dlist	**aux2;

	if (!lst || !*lst)
		return (NULL);
	aux1 = ft_dlstlast(*lst);
	aux2 = &aux1->prev;
	(*aux2)->next = NULL;
	aux1->prev = NULL;
	return (aux1);
}
