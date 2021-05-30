#include <libft.h>

ssize_t	ft_dlstsize(t_dlist *lst)
{
	t_dlist	*head;
	ssize_t	size;

	if (!lst)
		return (-1);
	head = ft_dlstfirst(lst);
	size = 1;
	while (head->next)
	{
		head = head->next;
		size++;
	}
	return (size);
}
