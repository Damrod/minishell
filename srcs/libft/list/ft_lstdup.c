#include <libft.h>

static t_list	*ft_lstdupclean(t_list **list, void (*dc)(), void (*dn)())
{
	if (*list)
		ft_lstclear(list, dc, dn);
	return (NULL);
}

static void	init_vars(void **a, void **b, void **c)
{
	*a = NULL;
	*b = NULL;
	*c = NULL;
}

t_list	*ft_lstdup(t_list *head, size_t contsize, void (*dc)(), void (*dn)())
{
	t_list	*node;
	t_list	*tmp;
	t_list	*head_ret;
	void	*content;

	init_vars((void **)&node, (void **)&tmp, (void **)&head_ret);
	while (head)
	{
		if (node)
			tmp = node;
		if (!na_malloc (contsize, (void **) & content) && head_ret)
			return (ft_lstdupclean(&head_ret, dc, dn));
		ft_memcpy(content, head->content, contsize);
		if (!na_lstnew(content, &node) && head_ret)
			return (ft_lstdupclean(&head_ret, dc, dn));
		if (!head_ret && node)
			head_ret = node;
		if (tmp)
			tmp->next = node;
		head = head->next;
	}
	if (node)
		node->next = NULL;
	return (head_ret);
}
