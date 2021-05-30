#include <libft.h>

void	ft_dlstffwd(t_dlist **lst)
{
	if (!lst || !(*lst))
		return ;
	*lst = ft_dlstlast(*lst);
}
