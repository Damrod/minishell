#include <libft.h>

void	btree_insert_data(t_btree **root, void *item,
						int (*cmpf)(void *, void *))
{
	t_btree	*new;

	if (!(*root))
	{
		new = btree_create_node(item);
		if (!new)
			return ;
		*root = new;
		return ;
	}
	if (cmpf((*root)->item, item) > 0)
		btree_insert_data(&(*root)->left, item, cmpf);
	else
		btree_insert_data(&(*root)->right, item, cmpf);
}
