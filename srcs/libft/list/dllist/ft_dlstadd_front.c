#include <libft.h>

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (!(new) || !(lst))
		return ;
	new->prev = NULL;
	new->next = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	*lst = ft_dlstfirst(*lst);
	(*lst)->prev = new;
	new->next = *lst;
	*lst = new;
	return ;
}
