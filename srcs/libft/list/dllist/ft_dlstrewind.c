#include <libft.h>

void	ft_dlstrewind(t_dlist **lst)
{
	if (!lst || !(*lst))
		return ;
	*lst = ft_dlstfirst(*lst);
}
