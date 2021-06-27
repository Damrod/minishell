#include <libft.h>

t_dlist	*na_dlstnew(void *content, t_dlist **ret_val)
{
	t_dlist	*list;

	list = NULL;
	if (!na_malloc(sizeof(*list), (void **) &list))
		return (NULL);
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return (*ret_val = list);
}
