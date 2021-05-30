#include <libft.h>

t_dlist	*ft_dlstpop_front(t_dlist **lst)
{
	t_dlist	*aux1;

	if (!lst || !*lst)
		return (NULL);
	aux1 = ft_dlstfirst(*lst);
	*lst = aux1->next;
	aux1->next = NULL;
	(*lst)->prev = NULL;
	return (aux1);
}
