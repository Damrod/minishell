#include <libft.h>

void	ft_dlstclear(t_dlist **lst, void (*delcnt)(void*),
			void (*delnde)(void*))
{
	t_dlist	*tmp;
	t_dlist	**head;

	head = lst;
	if (!(lst) || !(*lst))
		return ;
	tmp = *lst;
	while (tmp)
	{
		tmp = (*lst)->next;
		ft_lstdelone((t_list *)*lst, delcnt, delnde);
		(*lst) = tmp;
	}
	if (delnde)
		delnde(*head);
	return ;
}
