#include <libft.h>

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	if (!(lst) || !(new))
		return ;
	new->next = NULL;
	new->prev = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		new->prev = ft_dlstlast(*lst);
		ft_dlstlast(*lst)->next = new;
	}
	return ;
}
