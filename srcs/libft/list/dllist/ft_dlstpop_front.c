#include <libft.h>

t_dlist	*ft_dlstpop_front(t_dlist **lst)
{
	t_dlist	*aux1;

	if (!lst || !*lst)
		return (NULL);
	aux1 = ft_dlstfirst(*lst);
	if (aux1 == *lst && ft_lstsize((t_list *)aux1) <= 1)
		return (*lst);
	if (aux1)
	{
		*lst = aux1->next;
		aux1->next = NULL;
	}
	if (lst && *lst)
		(*lst)->prev = NULL;
	return (aux1);
}
