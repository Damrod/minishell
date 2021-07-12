#include <libft.h>

t_dlist	*ft_dlstpop_back(t_dlist **lst)
{
	t_dlist	*aux1;
	t_dlist	*aux2;

	if (!lst || !*lst)
		return (NULL);
	aux2 = NULL;
	aux1 = ft_dlstlast(*lst);
	if (aux1 == *lst && ft_lstsize((t_list *)ft_dlstfirst(*lst)) <= 1)
		return (*lst);
	if (aux1)
	{
		aux2 = aux1->prev;
		aux1->prev = NULL;
	}
	if (aux2)
		aux2->next = NULL;
	return (aux1);
}
